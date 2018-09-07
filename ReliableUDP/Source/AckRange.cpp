#include "stdafx.h"
#include "AckRange.h"


AckRange::AckRange() : mStart(0), mCount(0)
{
}


AckRange::AckRange(PacketSequenceNumber start) : 
	mStart(start), 
	mCount(1)
{
}


AckRange::AckRange(PacketSequenceNumber start, uint8_t cnt) : 
	mStart(start), 
	mCount(cnt)
{
}

AckRange::~AckRange()
{
}


bool AckRange::ExtendIfShould(PacketSequenceNumber inSequenceNumber)
{
	if (inSequenceNumber == mStart + mCount)
	{
		++mCount;
		return true;
	}
	else
	{
		return false;
	}
}

bool AckRange::ExtendIfShould(PacketSequenceNumber inSequenceNumber, uint8_t count)
{
	if (inSequenceNumber == mStart + mCount)
	{
		++mCount;
		return true;
	}
	else if (mStart == inSequenceNumber)
	{
		if (count > mCount)
			mCount = count;
		return true;
	}
	else
	{
		return false;
	}
}

void AckRange::Reduce(uint8_t count)
{
	if (count > mCount)
		std::cerr << "AckRange::Reduce wrong counter" << std::endl;
	mStart += count;
	mCount -= count;
}

PacketSequenceNumber AckRange::GetStart() const
{
	return mStart;
}

uint8_t AckRange::GetCount() const
{
	return mCount;
}

PacketSequenceNumber AckRange::GetEnd() const
{
	return mStart + mCount - 1;
}
