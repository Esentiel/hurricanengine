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
			mIndices->at(idx) = eFree;
			
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
	uint32_t nextIdx = 0;
	uint32_t retIdx = 0;

	for (uint32_t idx = mNextToAlloc; idx < mIndices->size(); )
	{
		nextIdx = idx + 1;

		if (idx)
		{
			if (blockSize == 1)
			{
				retIdx = idx;

				break;
			}
			else
			{
				uint32_t tRealSize = blockSize - 1;
				uint32_t tIdx = idx + 1;

				while (tRealSize && tIdx < mIndices->size())
				{
					if (mIndices->at(tIdx) != eFree)
					{
						break;
					}
					else
					{
						if (!--tRealSize)
						{
							retIdx = idx;

							break;
						}
						tIdx++;
					}
				}

				if (retIdx)
					break;
				else if (tIdx < mIndices->size())
					nextIdx = tIdx;
			}
		}
		else
		{
			retIdx = mNextToAlloc;
			break;
		}

		idx = nextIdx;
	}

	return retIdx;
}

uint32_t MemoryPool::GetIndex(void * ptr) const
{
	char * tmpPtr = (char*)ptr;
	const uint32_t idx = (uint32_t)(tmpPtr - mPool);

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