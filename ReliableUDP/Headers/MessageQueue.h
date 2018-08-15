#pragma once

#include "stdafx.h"
#include "MemoryStream.h"
#include "Message.h"

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
	void Enqueue(Message msg);

	~MessageQueue();
private:
	void PopFront();
	std::deque<Message> mMessages;
	uint8_t mLastSent;
};

