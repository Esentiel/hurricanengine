#pragma once

#include "stdafx.h"
#include "MemoryStream.h"

class MessageQueue
{
public:
	enum class WritingResult
	{
		eOK,
		eOKStop,
		eErrorProceed,
		eErrorStop
	};

	MessageQueue();
	
	void Ack(uint16_t seq, bool ack);
	void GetnextMessage(PacketSequenceNumber seq, MemoryStream *data, int &len);
	bool GetNextMessageLen(int &len) const;

	~MessageQueue();

private:
	struct Message
	{
		enum class MessageReliability { eReliable, eUnreliable };
		enum class MessageOrdering { eOrdered, eUnordered };
		enum class MessageType { eSerialization, eRMI, eFastMessage };
		enum class MessageStatus { eQueued, eSent, eOutdated };

		Message() {}
		~Message() { delete mData; }

		MemoryStream* mData; // TODO: get rid of raw pointer. [C2280] in case of unique_ptr
		uint8_t mSize;
		uint16_t mNetId;
		PacketSequenceNumber mSeq;
		MessageReliability mReliability;
		MessageOrdering mOrdering;
		MessageType mType;
		MessageStatus mMessageStatus;
	};

private:
	void Enqueue(Message msg);
	void PopFront();
	std::deque<Message> mMessages;
	uint8_t mLastSent;
};

