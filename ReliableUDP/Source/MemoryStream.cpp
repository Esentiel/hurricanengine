#include "stdafx.h"
#include "MemoryStream.h"


MemoryStream::MemoryStream(char* inBuffer, uint32_t inByteCount) : mBuffer(inBuffer), mCapacity(inByteCount), mHead(0)
{
}

MemoryStream::MemoryStream(MemoryStream&& rhs) : 
	mBuffer(rhs.mBuffer), 
	mHead(rhs.mHead), 
	mCapacity(rhs.mCapacity)
{
	rhs.mBuffer = nullptr;
	rhs.mHead = 0;
	rhs.mCapacity = 0;
}

NETWORKLIBRARY_API MemoryStream::~MemoryStream()
{
	std::free(mBuffer); // TODO: not safe
}

MemoryStream& MemoryStream::operator=(MemoryStream && rhs)
{
	if (&rhs == this)
		return *this;

	mBuffer = rhs.mBuffer;
	mHead = rhs.mHead;
	mCapacity = rhs.mCapacity;

	rhs.mBuffer = nullptr;
	rhs.mHead = 0;
	rhs.mCapacity = 0;

	return *this;
}

