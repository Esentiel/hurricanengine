#include "stdafx.h"
#include "MessageQueue.h"


MessageQueue::MessageQueue() :
	mLastSent(0)
{
}


void MessageQueue::Enqueue(Message msg)
{
	mMessages.push_back(std::move(msg));
	mMessages.back().mMessageStatus = Message::MessageStatus::eQueued;
}

void MessageQueue::Ack(uint16_t seq, bool ack)
{
	if (mMessages.size())
	{
		auto msg = mMessages.front();

		if (msg.mSeq == seq)
		{
			std::cout << "Ack: seq=" << seq << ", ack=" << ack << std::endl;
			if (ack)
			{
				PopFront();
			}
			else
			{
				if (msg.mReliability == Message::MessageReliability::eReliable)
				{
					Enqueue(msg);
					PopFront();
				}
				else
				{
					PopFront();
				}
			}
		}
		else
		{
			//std::cerr << "MessageQueue::Ack << wut?" << std::endl;
			//assert(false);
		}
	}
}

void MessageQueue::GetnextMessage(PacketSequenceNumber seq, MemoryStream **data, int &len)
{
	if (mLastSent + 1 >= mMessages.size())
		return;

	Message &msg = mMessages.at(mLastSent);
	*data = msg.mData;
	len = msg.mSize;

	msg.mSeq = seq;
	msg.mMessageStatus = Message::MessageStatus::eSent;
	mLastSent++;
}

bool MessageQueue::GetNextMessageLen(int &len) const
{
	if (mLastSent + 1 >= mMessages.size())
	{
		return false;
	}
	else
	{
		len = mMessages.at(mLastSent + 1).mSize;
		return true;
	}
}

MessageQueue::~MessageQueue()
{
}

void MessageQueue::PopFront()
{
	mMessages.pop_front();
	mLastSent--;
}
