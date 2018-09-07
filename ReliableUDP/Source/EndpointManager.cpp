#include "stdafx.h"
#include "EndpointManager.h"

#include "UDP/UDPSocket.h"
#include "UDP/SocketUtil.h"
#include "MemoryStream.h"

#include <sstream> //TODO

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
	ResetBufferSize();

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

	if (isSomethingToSend && ((mBufferSize + len < MAX_PACKET_SIZE) || mBufferSize == HEADER_SIZE))
	{
		mMsgQueue->GetnextMessage(mNextToSend, &data, len);
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
			WriteHeader();
			result = mSocket->SendTo(mBuffer->data(), mBufferSize, *mRecipient);
			//std::cout << "SendPacket: seq=" << mNextToSend << ", sent byteCnt=" << result << std::endl;
			std::cout << "Sent" << std::endl;
			if (result > 0)
			{
				mLastSentSeq++;
				mNextToSend = mLastSentSeq + 1;
				ResetBufferSize();
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

	std::stringstream log;
	log << "[OUTGOING] Write header: seq:" << mNextToSend;
	//LogDebug("[OUTGOING] Write header: seq: %d", mNextToSend);
	// acks
	if (mPendingAcks.size())
	{
		AckRange ackRangePending = mPendingAcks.front();
		mBuffer->at(2) = ackRangePending.GetStart() & 0xff;
		mBuffer->at(3) = (ackRangePending.GetStart() >> 8) & 0xff;
		mBuffer->at(4) = ackRangePending.GetCount() & 0xff;

		log << ", ack:" << (int)ackRangePending.GetStart() << ", ackCnt:" << (int)ackRangePending.GetCount();
	}
	else
	{
		mBuffer->at(2) = 0;
		mBuffer->at(3) = 0;
		mBuffer->at(4) = 0;

		log << ", ack:" << 0 << ", ackCnt:" << 0;
	}

	// confirm acks received
	if (mConfirmAcks.size())
	{
		const AckRange &ackRangeConfirm = mConfirmAcks.front();
		mBuffer->at(5) = ackRangeConfirm.GetStart() & 0xff;
		mBuffer->at(6) = (ackRangeConfirm.GetStart() >> 8) & 0xff;
		mBuffer->at(7) = ackRangeConfirm.GetCount() & 0xff;

		log << ", ackConfirm:" << (int)ackRangeConfirm.GetStart() << ", ackConfirmCnt:" << (int)ackRangeConfirm.GetCount();
	}
	else
	{
		mBuffer->at(5) = 0;
		mBuffer->at(6) = 0;
		mBuffer->at(7) = 0;

		log << ", ackConfirm:" << 0 << ", ackConfirmCnt:" << 0;
	}

	std::cout << log.str() << std::endl;
	LogDebug(log.str());
	//mBufferSize = HEADER_SIZE;
}

void EndpointManager::ReadHeader(const std::array<char, MAX_PACKET_SIZE> *buffer)
{
	PacketSequenceNumber seq;
	PacketSequenceNumber ack;
	PacketSequenceNumber ackConfirm;
	uint8_t ackCnt;
	uint8_t ackConfirmCnt;

	seq = buffer->at(0) | (buffer->at(1) << 4);
	ack = buffer->at(2) | (buffer->at(3) << 4);
	ackCnt = buffer->at(4);
	ackConfirm = buffer->at(5) | (buffer->at(6) << 4);
	ackConfirmCnt = buffer->at(7);

	 std::stringstream ss;
	 ss << "[INCOMING] Read header: seq:" << seq << ", ack:" << ack << ", ackCnt:" << (int)ackCnt << ", ackConfirm:" << ackConfirm << ", ackConfirmCnt:" << (int)ackConfirmCnt << std::endl;
	 std::cout << ss.str() << std::endl;
	 LogDebug(ss.str());
	// send back to let know that we received seq packet
	if (seq)
	{
		if (mPendingAcks.size())
		{
			AckRange &ackRangePending = mPendingAcks.back();
			if (!ackRangePending.ExtendIfShould(seq))
				mPendingAcks.emplace_back(AckRange(seq));
		}
		else
		{
			mPendingAcks.emplace_back(AckRange(seq));
		}
	}

	// store received acks to send back confirmation
	//if (ack)
	//{
	//	if (mConfirmAcks.size())
	//	{
	//		AckRange &ackRangeConfirmed = mConfirmAcks.back();
	//		if (!ackRangeConfirmed.ExtendIfShould(ack))
	//			mConfirmAcks.emplace_back(AckRange(ack, ackCnt));
	//	}
	//	else
	//	{
	//		mConfirmAcks.emplace_back(AckRange(ack, ackCnt));
	//	}
	//}




	ProcessAcks(ack, ackCnt, ackConfirm, ackConfirmCnt);
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
		if (streamSize > 0)
		{
			char * data = (char*)std::malloc(streamSize * sizeof(char)); // memory stream owns data
			memcpy(data, &(buffer->data()[headIdx]), streamSize); // TODO: rewrite this shit
			InputMemoryBitStream memStream(data, streamSize);
			streams.push_back(std::move(memStream));

			headIdx += streamSize;
		}
		else
		{
			break;
		}
	}

	return streams;

}

void EndpointManager::ResetBufferSize()
{
	mBufferSize = HEADER_SIZE;
}

void EndpointManager::ProcessAcks(PacketSequenceNumber ack, uint8_t ackCount, PacketSequenceNumber ackConfirm, uint8_t ackConfirmCnt)
{
	PacketSequenceNumber last = ack + ackCount;

	if (last)
	{
		for (PacketSequenceNumber currAckSeq = mLastAckedSeq; currAckSeq <= last; currAckSeq++)
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
				//std::cerr << "WTF processing ack?" << std::endl;
				//assert(false);
			}
		}
	}

	// add pending acks
	if (ack)
	{
		//bool isAdded = false;
		if (mConfirmAcks.size())
		{
			//isAdded = true;
			AckRange &ackRangeConfirmedBack = mConfirmAcks.back();
			if (!ackRangeConfirmedBack.ExtendIfShould(ack, ackCount))
				mConfirmAcks.emplace_back(AckRange(ack, ackCount));

		}
		else
		{
			mConfirmAcks.emplace_back(AckRange(ack, ackCount));
		}

		std::string logLine;
		for (auto &el : mConfirmAcks)
		{
			logLine.append("[add confirm acks] mConfirmAcks: start: " + std::to_string(el.GetStart()) + ", count: " + std::to_string(el.GetCount()));
			LogDebug(logLine);
			logLine.clear();
		}

		/*if (isAdded)
		{
			AckRange &ackRangeConfirmed = mConfirmAcks.front();
			if (ack != ackRangeConfirmed.GetStart())
			{
				if (ack < ackRangeConfirmed.GetEnd())
					ackRangeConfirmed.Reduce(ack - 1);
				else if (ack == ackRangeConfirmed.GetEnd())
					mConfirmAcks.pop_front();
			}
		}*/
	}



	// remove already confirmed acks
	if (ack && mConfirmAcks.size())
	{
		AckRange &ackRangeConfirmed = mConfirmAcks.front();
		if (ackRangeConfirmed.GetStart() < ack && ackRangeConfirmed.GetEnd() <= ack)
		{
			ackRangeConfirmed.Reduce(ack - ackRangeConfirmed.GetStart());
		}
		//else if (ackRangeConfirmed.GetStart() == ack)
		//{
		//	mConfirmAcks.pop_back();
		//}

		std::string logLine;
		for (auto &el : mConfirmAcks)
		{
			logLine.append("[remove already confirmed acks] mConfirmAcks: start: " + std::to_string(el.GetStart()) + ", count: " + std::to_string(el.GetCount()));
			LogDebug(logLine);
			logLine.clear();
		}
	}

	

	// remove from ack queue those which are confirmed
	if (mPendingAcks.size() && ackConfirm)
	{
		AckRange &firstAck = mPendingAcks.front();
		if (firstAck.GetStart() == ackConfirm && firstAck.GetCount() == ackConfirmCnt)
		{
			mPendingAcks.pop_front();
		}
		else if (firstAck.GetStart() == ackConfirm)
		{
			firstAck.Reduce(ackConfirmCnt);
		}
		else
		{
			std::cerr << "Wrong pending ack" << std::endl;
			//assert(false);
		}

		std::string logLine;
		for (auto &el : mPendingAcks)
		{
			logLine.append("[remove from pend ack] mPendingAcks: start: " + std::to_string(el.GetStart()) + ", count: " + std::to_string(el.GetCount()));
			LogDebug(logLine);
			logLine.clear();
		}
	}
}
