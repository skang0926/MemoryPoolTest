

#include "MemoryPool.h"

MemoryPool::MemoryPool(int size)
{
	memoryPool = new FMemoryBlock[size];
	memoryPoolSize = size;
	for (int i = 0; i < size; ++i)
	{
		indexList.push_back(i);
	}
}

MemoryPool::~MemoryPool()
{
	if (memoryPool != nullptr)
		delete[] memoryPool;
}

void* MemoryPool::Alloc()
{	
	if (indexList.empty()) return nullptr;

	void* memory = reinterpret_cast<void*>(&memoryPool[indexList.front()]);
	indexList.pop_front();
	return memory;
}

void MemoryPool::Free(void* memory)
{	
	if (memory == nullptr) return;

	FMemoryBlock* memoryPtr = reinterpret_cast<FMemoryBlock*>(memory);
	int memoryIndex = memoryPtr - &memoryPool[0];

	if (memoryIndex >= memoryPoolSize && memoryIndex < 0)
		return;

	indexList.push_front(memoryIndex);

	return;
}