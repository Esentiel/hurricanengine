#pragma once

#ifdef NETWORKLIBRARY_EXPORTS
#define NETWORKLIBRARY_API __declspec(dllexport)
#else
#define NETWORKLIBRARY_API __declspec(dllimport)
#endif

class DeliveryNotificationManager;

class TransmissionData
{
public:
	NETWORKLIBRARY_API TransmissionData();
	NETWORKLIBRARY_API ~TransmissionData();
	NETWORKLIBRARY_API virtual void HandleDeliveryFailure(DeliveryNotificationManager*) = 0;
	NETWORKLIBRARY_API virtual void HandleDeliverySuccess(DeliveryNotificationManager*) = 0;
};

