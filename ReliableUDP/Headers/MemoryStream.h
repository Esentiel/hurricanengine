#pragma once

#ifdef NETWORKLIBRARY_EXPORTS
#define NETWORKLIBRARY_API __declspec(dllexport)
#else
#define NETWORKLIBRARY_API __declspec(dllimport)
#endif

class MemoryStream
{
public:
	NETWORKLIBRARY_API MemoryStream(char* inBuffer, uint32_t inByteCount);

	NETWORKLIBRARY_API const char* GetBufferPtr() const { return mBuffer; }
	NETWORKLIBRARY_API uint32_t GetLength() const { return mHead; }

	NETWORKLIBRARY_API virtual ~MemoryStream();

	MemoryStream(MemoryStream&) = delete;
	MemoryStream& operator=(MemoryStream) = delete;
protected:
	char* mBuffer;
	uint32_t mHead;
	uint32_t mCapacity;
};

