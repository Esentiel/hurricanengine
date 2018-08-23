#include "stdafx.h"
#include "MemoryStream.h"


MemoryStream::MemoryStream(char* inBuffer, uint32_t inByteCount) : mBuffer(inBuffer), mCapacity(inByteCount), mHead(0)
{
}

NETWORKLIBRARY_API MemoryStream::~MemoryStream()
{
	std::free(mBuffer); // TODO: not safe
}

