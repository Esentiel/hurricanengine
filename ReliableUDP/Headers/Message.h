#include "stdafx.h"
#include "MemoryStream.h"

struct Message
{
	enum class MessageReliability { eReliable, eUnreliable };
	enum class MessageOrdering { eOrdered, eUnordered };
	enum class MessageType { eSerialization, eRMI, eFastMessage };
	enum class MessageStatus { eQueued, eSent, eOutdated };

	Message();
	~Message();

	MemoryStream* mData; // TODO: get rid of raw pointer. [C2280] in case of unique_ptr
	uint8_t mSize;
	uint16_t mNetId;
	PacketSequenceNumber mSeq;
	MessageReliability mReliability;
	MessageOrdering mOrdering;
	MessageType mType;
	MessageStatus mMessageStatus;
};
