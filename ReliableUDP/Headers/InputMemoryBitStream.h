#pragma once

#include "MemoryStream.h"

#ifdef NETWORKLIBRARY_EXPORTS
#define NETWORKLIBRARY_API __declspec(dllexport)
#else
#define NETWORKLIBRARY_API __declspec(dllimport)
#endif

class InputMemoryBitStream :
	public MemoryStream
{
public:
	NETWORKLIBRARY_API InputMemoryBitStream(char * inBuffer, int inHead);
	NETWORKLIBRARY_API void ReadBits(uint8_t& outData, uint32_t inBitCount);
	NETWORKLIBRARY_API void ReadBits(void* outData, uint32_t inBitCount);
	NETWORKLIBRARY_API ~InputMemoryBitStream();

	template<typename T>
	void Read(T& inData, uint32_t inBitCount = sizeof(T) * 8)
	{
		static_assert(std::is_arithmetic<T>::value ||
			std::is_enum<T>::value,
			"Generic Read only supports primitive data types");
		ReadBits(&inData, inBitCount);
	}

	template<typename bool>
	void Read(bool inData, size_t inBitCount = 1)
	{
		ReadBits(&inData, inBitCount);
	}
};

