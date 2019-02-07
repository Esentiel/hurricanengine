#pragma once

#include <cstdint>
#include <array>

#ifdef _DEBUG
#include <iostream>
#endif

#define POOL_SIZE 67108864 // 64MB
#define ALIGNMENT 64


class MemoryPool
{
public:
	MemoryPool();
	virtual ~MemoryPool();

	void* alloc(size_t size);
	void dealloc(void * ptr);
	void reset();

	bool belongs(void * ptr) const;

	void * operator new(size_t size)
	{
		void * ptr = std::malloc(size);

		return ptr;
	}

	void operator delete(void * ptr)
	{
		free(ptr);
	}
#ifdef _DEBUG
	void dump(size_t size)
	{
		for (int i = 0; i < size; i++)
			std::cout << "idx: " << i << ", val = " << mIndices->at(i) << "\n";
	}
#endif

protected:
	enum BlockState {eFree, eHead, eTail};
	uint32_t FindForAllocation(uint32_t blockSize) const;
	uint32_t GetIndex(void * ptr) const;
	void ReserveBlocks(uint32_t idx, uint32_t size);
	uint32_t FindNextFree(uint32_t start) const;

	const uint64_t mPoolSize;
	const uint32_t mIndicesSize;
	char* mPool;
	std::unique_ptr<std::array<BlockState, POOL_SIZE / ALIGNMENT>> mIndices;
	uint32_t mNextToAlloc;
};

