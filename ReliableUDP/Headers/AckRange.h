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
	bool ExtendIfShould(PacketSequenceNumber inSequenceNumber, uint8_t count);
	void Reduce(uint8_t count);
	PacketSequenceNumber GetStart() const;
	uint8_t GetCount() const;
	PacketSequenceNumber GetEnd() const;
private:
	uint8_t mCount;
	PacketSequenceNumber mStart;
};

