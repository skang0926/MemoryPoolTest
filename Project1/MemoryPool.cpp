

#include "MemoryPool.h"

template <typename T>
MemoryPool<T>::MemoryPool(int size)
{
	memoryPool = new T[size];
	memoryPoolSize = size;
	for (int i = 0; i < size; ++i)
	{
		indexList.push_back(i);
	}
}

template <typename T>
MemoryPool<T>::~MemoryPool()
{
	if (memoryPool != nullptr)
		delete[] memoryPool;
}


template <typename T>
void* MemoryPool<T>::Alloc()
{	
	if (indexList.empty()) return nullptr;

	void* memory = reinterpret_cast<void*>(&memoryPool[indexList.front()]);
	indexList.pop_front();
	return memory;
}

template <typename T>
void MemoryPool<T>::Free(void* memory)
{	
	if (memory == nullptr) return;

	T* memoryPtr = reinterpret_cast<T*>(memory);
	int memoryIndex = memoryPtr - &memoryPool[0];

	if (memoryIndex >= memoryPoolSize && memoryIndex < 0)
		return;

	indexList.push_front(memoryIndex);

	return;
}