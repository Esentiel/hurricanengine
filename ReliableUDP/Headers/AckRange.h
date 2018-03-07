#pragma once

#include "OutputMemoryBitStream.h"
#include "InputMemoryBitStream.h"

#ifdef NETWORKLIBRARY_EXPORTS
#define NETWORKLIBRARY_API __declspec(dllexport)
#else
#define NETWORKLIBRARY_API __declspec(dllimport)
#endif

using PacketSequenceNumber = uint16_t;

class AckRange
{
public:
	NETWORKLIBRARY_API AckRange();
	NETWORKLIBRARY_API AckRange(PacketSequenceNumber start);
	NETWORKLIBRARY_API ~AckRange();

	NETWORKLIBRARY_API bool ExtendIfShould(PacketSequenceNumber inSequenceNumber);
	NETWORKLIBRARY_API void Write(OutputMemoryBitStream& inPacket) const;
	NETWORKLIBRARY_API void Read(InputMemoryBitStream& inPacket);
	NETWORKLIBRARY_API PacketSequenceNumber GetStart() const;
	NETWORKLIBRARY_API PacketSequenceNumber GetCount() const;
private:
	uint16_t mCount;
	PacketSequenceNumber mStart;
};

