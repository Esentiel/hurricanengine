#include "stdafx.h"
#include "MessageQueue.h"


MessageQueue::MessageQueue() :
	mLastSent(0)
{
}


void MessageQueue::Enqueue(Message msg)
{
	mMessages.push_back(msg);
	mMessages.back().mMessageStatus = Message::MessageStatus::eQueued;
}

void MessageQueue::Ack(uint16_t seq, bool ack)
{
	auto msg = mMessages.front();

	if (msg.mSeq != seq)
	{
		assert(false);
	}	

	while (msg.mSeq == seq)
	{
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
}

void MessageQueue::GetnextMessage(PacketSequenceNumber seq, MemoryStream *data, int &len)
{
	if (mLastSent + 1 >= mMessages.size())
		return;

	auto msg = mMessages.at(mLastSent + 1);
	data = msg.mData;
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
