#pragma once
#include "MemoryPool.h"
class DefragMemoryPool :
	public MemoryPool
{
public:
	DefragMemoryPool();
	virtual ~DefragMemoryPool();
};

