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

PacketSequenceNumber AckRange::GetStart() const
{
	return mStart;
}

uint8_t AckRange::GetCount() const
{
	return mCount;
}
