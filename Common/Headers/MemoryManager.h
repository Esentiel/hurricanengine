#pragma once

#include "MemoryPool.h"

#define MAX_ALLOC_SIZE 64000

void* operator new(std::size_t sz);
void operator delete(void* ptr);


class MemoryManager
{
public:
	static void Initialize();
	static void * Allocate(std::size_t sz);
	static void Deallocate(void * ptr);

#ifdef _DEBUG
	static void dump(size_t size)
	{
		mMemPool->dump(size);
	}
#endif

	MemoryManager() = delete;
private:
	static std::unique_ptr<MemoryPool> mMemPool;
};

