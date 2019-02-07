#include "MemoryPool.h"


#include <algorithm>



MemoryPool::MemoryPool() : 
	mPoolSize(POOL_SIZE),
	mIndicesSize(POOL_SIZE / ALIGNMENT),
	mPool(nullptr),
	mIndices(new std::array<BlockState, POOL_SIZE / ALIGNMENT>()),
	mNextToAlloc(0)
{
	mPool = (char*)std::malloc(mPoolSize);
}


MemoryPool::~MemoryPool()
{
	free(mPool);
}

void * MemoryPool::alloc(size_t size)
{
	uint32_t blockSize = (uint32_t)size < ALIGNMENT ? 1 : (uint32_t)size / ALIGNMENT + 1;
	// find empty space
	uint32_t idx = FindForAllocation(blockSize);

	// reserve blocks
	ReserveBlocks(idx, blockSize);

	// return pointer
	void * ptr = mPool + idx * ALIGNMENT;
	
	return ptr;
}

void MemoryPool::dealloc(void * ptr)
{
	const uint32_t idx = GetIndex(ptr);
	if (belongs(ptr))
	{
		uint32_t tmpIdx = idx;
		do
		{
			mIndices->at(tmpIdx) = eFree;
			tmpIdx++;
			
		} while (mIndices->at(tmpIdx) != eFree && mIndices->at(tmpIdx) != eHead);

		mNextToAlloc = idx;
	}
}

void MemoryPool::reset()
{
	std::for_each(mIndices->begin(), mIndices->end(), [&](BlockState &val) { val = eFree; });
	mNextToAlloc = 0;
}

bool MemoryPool::belongs(void * ptr) const
{
	const uint32_t idx = GetIndex(ptr);

	return idx < POOL_SIZE;
}

uint32_t MemoryPool::FindForAllocation(uint32_t blockSize) const
{
	uint32_t currHead = mNextToAlloc;
	uint32_t currIdx = mNextToAlloc;
	uint32_t currSize = 1;

	while(currSize != blockSize && currIdx + 1 < mIndices->size())
	{
		if (mIndices->at(currIdx + 1) == eFree)
		{
			currSize++;
		}
		else
		{
			currSize = 1;
			currHead = FindNextFree(currIdx);
		}

		currIdx++;
	}

	return currHead;
}

uint32_t MemoryPool::GetIndex(void * ptr) const
{
	char * tmpPtr = (char*)ptr;
	const uint32_t idx = (tmpPtr - mPool) / ALIGNMENT;

	return idx;
}

void MemoryPool::ReserveBlocks(uint32_t idx, uint32_t size)
{
	for (uint32_t i = idx; i < idx + size; i++)
	{
		if (i == idx)
			mIndices->at(i) = eHead;
		else
			mIndices->at(i) = eTail;
	}

	mNextToAlloc = idx + size;
	
}

uint32_t MemoryPool::FindNextFree(uint32_t start) const
{
	auto it = std::find_if(mIndices->cbegin() + start, mIndices->cend(), [&](const BlockState &state) { return state == BlockState::eFree; });

	return std::distance(mIndices->cbegin(), it);
}
