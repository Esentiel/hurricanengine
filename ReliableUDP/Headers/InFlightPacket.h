#pragma once

#include "TransmissionData.h"

#ifdef NETWORKLIBRARY_EXPORTS
#define NETWORKLIBRARY_API __declspec(dllexport)
#else
#define NETWORKLIBRARY_API __declspec(dllimport)
#endif

class DeliveryNotificationManager;
using TransmissionDataPtr = std::shared_ptr<TransmissionData>;
using PacketSequenceNumber = uint16_t;

class InFlightPacket
{
public:
	NETWORKLIBRARY_API InFlightPacket(PacketSequenceNumber secNumber);
	NETWORKLIBRARY_API ~InFlightPacket();
	NETWORKLIBRARY_API void SetTransmissionData(int inKey, TransmissionDataPtr inTransmissionData);
	NETWORKLIBRARY_API const TransmissionDataPtr GetTransmissionData(int inKey) const;
	NETWORKLIBRARY_API void HandleDeliveryFailure(DeliveryNotificationManager* inDeliveryNotificationManager) const;
	NETWORKLIBRARY_API void HandleDeliverySuccess(DeliveryNotificationManager* inDeliveryNotificationManager) const;
	NETWORKLIBRARY_API PacketSequenceNumber GetSequenceNumber() const;
	NETWORKLIBRARY_API float GetTimeDispatched() const;
private:
	PacketSequenceNumber mSequenceNumber;
	float mTimeDispatched;
	std::unordered_map<int, TransmissionDataPtr> mTransmissionDataMap;
};

