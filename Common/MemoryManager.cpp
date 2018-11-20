#include "MemoryManager.h"


void* operator new(std::size_t sz)
{
	std::cout << "my new" << std::endl;
	return MemoryManager::Allocate(sz);
};

void operator delete(void* ptr)
{
	std::cout << "my delete" << std::endl;
	MemoryManager::Deallocate(ptr);
};

std::unique_ptr<MemoryPool> MemoryManager::mMemPool;

void MemoryManager::Initialize()
{
	mMemPool.reset(new MemoryPool);
}

void * MemoryManager::Allocate(std::size_t sz)
{
	if (sz > MAX_ALLOC_SIZE)
		return std::malloc(sz);
	else
		return mMemPool->alloc(sz);
}

void MemoryManager::Deallocate(void * ptr)
{
	if (mMemPool->belongs(ptr))
		mMemPool->dealloc(ptr);
	else
		std::free(ptr);
}