#pragma once

#include "OutputMemoryBitStream.h"
#include "InputMemoryBitStream.h"

using PacketSequenceNumber = uint16_t;

class AckRange
{
public:
	AckRange();
	AckRange(PacketSequenceNumber start);
	AckRange(PacketSequenceNumber start, uint8_t cnt);
	~AckRange();

	bool ExtendIfShould(PacketSequenceNumber inSequenceNumber);
	PacketSequenceNumber GetStart() const;
	uint8_t GetCount() const;
private:
	uint8_t mCount;
	PacketSequenceNumber mStart;
};

