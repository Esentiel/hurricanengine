#pragma once

#include "OutputMemoryBitStream.h"
#include "InputMemoryBitStream.h"
#include "InFlightPacket.h"
#include "AckRange.h"

#ifdef NETWORKLIBRARY_EXPORTS
#define NETWORKLIBRARY_API __declspec(dllexport)
#else
#define NETWORKLIBRARY_API __declspec(dllimport)
#endif

using PacketSequenceNumber = uint16_t;

class DeliveryNotificationManager
{
public:
	NETWORKLIBRARY_API DeliveryNotificationManager();
	NETWORKLIBRARY_API ~DeliveryNotificationManager();

	NETWORKLIBRARY_API InFlightPacket* WriteSequenceNumber(OutputMemoryBitStream& inPacket);
	NETWORKLIBRARY_API bool ProcessSequenceNumber(InputMemoryBitStream& inPacket);
	NETWORKLIBRARY_API void AddPendingAck(PacketSequenceNumber inSequenceNumber);
	NETWORKLIBRARY_API void WritePendingAcks(OutputMemoryBitStream& inPacket);
	NETWORKLIBRARY_API void ProcessAcks(InputMemoryBitStream& inPacket);
	NETWORKLIBRARY_API void ProcessTimedOutPackets();
	NETWORKLIBRARY_API void HandlePacketDeliveryFailure(const InFlightPacket& inFlightPacket);
	NETWORKLIBRARY_API void HandlePacketDeliverySuccess(const InFlightPacket& inFlightPacket);
private:
	PacketSequenceNumber mNextOutgoingSequenceNumber;
	PacketSequenceNumber mDispatchedPacketCount;
	PacketSequenceNumber mNextExpectedSequenceNumber;
	PacketSequenceNumber mDroppedPacketCount;
	PacketSequenceNumber mDeliveredPacketCount;
	const uint32_t kAckTimeout;
	std::deque<InFlightPacket> mInFlightPackets;
	std::deque<AckRange> mPendingAcks;
};

