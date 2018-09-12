#pragma once

#include "MemoryStream.h"

#ifdef NETWORKLIBRARY_EXPORTS
#define NETWORKLIBRARY_API __declspec(dllexport)
#else
#define NETWORKLIBRARY_API __declspec(dllimport)
#endif

class OutputMemoryBitStream : public MemoryStream
{
public:
	NETWORKLIBRARY_API OutputMemoryBitStream();

	NETWORKLIBRARY_API uint32_t GetBitLength() const { return mHead; }
	NETWORKLIBRARY_API uint32_t GetByteLength() const { return (mHead + 7) >> 3; }

	NETWORKLIBRARY_API void WriteBits(uint8_t inData, size_t inBitCount);
	NETWORKLIBRARY_API void WriteBits(const void* inData, size_t inBitCount);

	template<typename T>
	void Write(T inData, size_t inBitCount = sizeof(T) * 8)
	{
		static_assert(std::is_arithmetic<T>::value ||
			std::is_enum<T>::value,
			"Generic Write only supports primitive data types");
		WriteBits(&inData, inBitCount);
	}

	template<typename bool>
	void Write(bool inData, size_t inBitCount = 1)
	{
		WriteBits(&inData, inBitCount);
	}

	OutputMemoryBitStream(OutputMemoryBitStream&) = delete;
	OutputMemoryBitStream& operator=(OutputMemoryBitStream) = delete;

private:
	void ReallocBuffer(uint32_t inNewBitCapacity);
};

