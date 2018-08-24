#include "stdafx.h"
#include "EndpointManager.h"

#include "UDP/UDPSocket.h"
#include "UDP/SocketUtil.h"
#include "MemoryStream.h"


EndpointManager::EndpointManager(UDPSocket* socket, SocketAddress addr) :
	mSocket(socket),
	mRecipient(std::make_unique<SocketAddress>(addr)),
	mLastSentSeq(0),
	mNextToSend(1),
	mLastAckedSeq(0),
	mMsgQueue(std::make_unique<MessageQueue>()),
	mBuffer(std::make_unique<std::array<char, MAX_PACKET_SIZE>>()),
	mBufferSize(0)
{
}

EndpointManager::~EndpointManager()
{
}

void EndpointManager::SendAll()
{	
	ResetBuffer();

	MessageQueue::WritingResult result;
	do 
	{
		result = WriteMsg();
	} while (result != MessageQueue::WritingResult::eErrorStop && result != MessageQueue::WritingResult::eOKStop);

	if (result == MessageQueue::WritingResult::eErrorStop)
	{
		SocketUtil::ReportError(L"SendAll() failed to send packet!");
		SocketUtil::GetLastError();
		// TODO: break the connection
	}
}

MessageQueue::WritingResult EndpointManager::WriteMsg()
{
	bool isSomethingToSend(false);
	int result(0);
	MemoryStream * data(nullptr);
	int len(0);

	isSomethingToSend = mMsgQueue->GetNextMessageLen(len);

	if (isSomethingToSend && (mBufferSize + len < MAX_PACKET_SIZE))
	{
		mMsgQueue->GetnextMessage(mNextToSend, data, len);
		if (data)
		{
			const char * rawData = data->GetBufferPtr();
			if (rawData)
			{
				std::copy(rawData, rawData + len, std::begin(*mBuffer) + mBufferSize);
				mBufferSize += len;
			}
		}
	}
	else
	{
		if (mBufferSize > HEADER_SIZE)
		{
			result = mSocket->SendTo(mBuffer->data(), mBufferSize, *mRecipient);
			if (result > 0)
			{
				mLastSentSeq++;
				mNextToSend = mLastSentSeq + 1;
				ResetBuffer();
			}
			else
			{
				if (++mSendCounter > MAX_SEND_ATTEMPTS)
				{
					mSendCounter = 0;
					return MessageQueue::WritingResult::eErrorStop;
				}
			}
		}
		else
		{
			return MessageQueue::WritingResult::eOKStop;
		}
	}

	if (result >= 0)
		return MessageQueue::WritingResult::eOK;
	else
		return MessageQueue::WritingResult::eErrorProceed;
}

void EndpointManager::WriteHeader()
{
	// seq
	mBuffer->at(0) = mNextToSend & 0xff;
	mBuffer->at(1) = (mNextToSend >> 8) & 0xff;

	// acks
	if (mPendingAcks.size())
	{
		AckRange ackRangePending = mPendingAcks.front();
		mBuffer->at(2) = ackRangePending.GetStart() & 0xff;
		mBuffer->at(3) = (ackRangePending.GetStart() >> 8) & 0xff;
		mBuffer->at(4) = ackRangePending.GetCount() & 0xff;
	}

	// confirm acks received
	if (mConfirmAcks.size())
	{
		AckRange ackRangeConfirm = mConfirmAcks.front();
		mBuffer->at(5) = ackRangeConfirm.GetStart() & 0xff;
		mBuffer->at(6) = (ackRangeConfirm.GetStart() >> 8) & 0xff;
		mBuffer->at(7) = ackRangeConfirm.GetCount() & 0xff;
	}

	mBufferSize = HEADER_SIZE;
}

void EndpointManager::ReadHeader(const std::array<char, MAX_PACKET_SIZE> *buffer)
{
	PacketSequenceNumber seq;
	PacketSequenceNumber ack;
	PacketSequenceNumber ackConfirm;
	uint8_t ackCnt;
	uint8_t ackConfirmCnt;

	seq &= buffer->at(0) | (buffer->at(1) << 4);
	ack &= buffer->at(2) | (buffer->at(3) << 4);
	ackCnt &= buffer->at(4);
	ackConfirm &= buffer->at(5) | (buffer->at(3) << 6);
	ackConfirmCnt &= buffer->at(7);

	// send back to let know that we received seq packet
	if (mPendingAcks.size())
	{
		AckRange ackRangePending = mPendingAcks.back();
		if (!ackRangePending.ExtendIfShould(seq))
			mPendingAcks.emplace_back(AckRange(seq));
	}
	else
	{
		mPendingAcks.emplace_back(AckRange(seq));
	}

	// store received acks to send back confirmation
	if (mConfirmAcks.size())
	{
		AckRange ackRangeConfirmed = mConfirmAcks.back();
		if (!ackRangeConfirmed.ExtendIfShould(ack))
			mConfirmAcks.emplace_back(AckRange(ack, ackCnt));
	}
	else
	{
		mConfirmAcks.emplace_back(AckRange(ack, ackCnt));
	}


	// remove from ack queue those which are confirmed
	if (mPendingAcks.size())
	{
		AckRange firstAck = mPendingAcks.front();
		if (firstAck.GetStart() == ackConfirm && firstAck.GetCount() == ackConfirmCnt)
		{
			mPendingAcks.pop_front();
		}
		else
		{
			std::cerr << "Wrong pending ack" << std::endl;
			//assert(false);
		}
	}

	ProcessAcks(ack, ackCnt);
}

void EndpointManager::PushToQueue(Message msg)
{
	mMsgQueue->Enqueue(std::move(msg));
}

std::vector<InputMemoryBitStream> EndpointManager::ReadData(const std::array<char, MAX_PACKET_SIZE> *buffer)
{
	std::vector<InputMemoryBitStream> streams;
	size_t headIdx = HEADER_SIZE;
	while (headIdx < buffer->size())
	{
		const int streamSize = buffer->at(headIdx);
		if (streamSize)
		{
			char * data = (char*)std::malloc(streamSize * sizeof(char)); // memory stream owns data
			memcpy(data, &(buffer->data()[headIdx]), streamSize); // TODO: rewrite this shit
			InputMemoryBitStream memStream(data, streamSize);
			streams.push_back(std::move(memStream));

			headIdx += streamSize;
		}
	}

	return streams;

}

void EndpointManager::ResetBuffer()
{
	//clear array
	// std::fill(std::begin(*mBuffer), std::end(*mBuffer), 0); TODO: seems not needed

	//fill header
	WriteHeader();

}

void EndpointManager::ProcessAcks(PacketSequenceNumber ack, uint8_t ackCount)
{
	PacketSequenceNumber last = ack + ackCount;

	for (PacketSequenceNumber currAckSeq = mLastAckedSeq; currAckSeq < last; currAckSeq++)
	{
		if (mLastAckedSeq + 1 < currAckSeq)
		{
			mMsgQueue->Ack(currAckSeq, false);
			mLastAckedSeq++;
		}
		else if (mLastAckedSeq + 1 == currAckSeq)
		{
			mMsgQueue->Ack(currAckSeq, true);
			mLastAckedSeq++;
		}
		else
		{
			std::cerr << "WTF processing ack?" << std::endl;
			//assert(false);
		}
			
	}
}
