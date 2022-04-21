#pragma once

#include <crtdbg.h>

using namespace std;

struct FMemoryBlock64
{
	char buffer[64];
};

struct FMemoryBlock128
{
	char buffer[128];
};

struct FMemoryBlock256
{
	char buffer[256];
};

template <typename T = FMemoryBlock64>
class MemoryPool
{
public:
	MemoryPool(size_t size);
	~MemoryPool();

	void* Alloc(int&& memorySize);

	void Free(void* memory);

private:
	char* pivot = nullptr;
	char* memoryPoolPtr = nullptr;
};



template <typename T>
MemoryPool<T>::MemoryPool(size_t size)
{
	memoryPoolPtr = new char[sizeof(T) * size];
	pivot = memoryPoolPtr;

	char** cur = reinterpret_cast<char**>(memoryPoolPtr);
	char* next = memoryPoolPtr;

	for (size_t i = 0; i < size - 1; ++i)
	{
		next += sizeof(T);
		*cur = next;
		cur = reinterpret_cast<char**>(next);
	}

	*cur = nullptr;
}

template <typename T>
MemoryPool<T>::~MemoryPool()
{
	if (memoryPoolPtr != nullptr)
		delete[] memoryPoolPtr;
}

template <typename T>
void* MemoryPool<T>::Alloc(int&& memorySize)
{
	if (memorySize > sizeof(T))
	{
		_ASSERT_EXPR(false, L"MemoryBlock's size exceeded");
		return nullptr;
	}

	if (pivot == nullptr)
	{
		_ASSERT_EXPR(false, L"MemoryPool is full");
		return nullptr;
	}

	char* memoryPtr = pivot;
	pivot = *reinterpret_cast<char**>(pivot);
	return reinterpret_cast<void*>(memoryPtr);
}

template <typename T>
void MemoryPool<T>::Free(void* memory)
{
	*reinterpret_cast<char**>(memory) = pivot;
	pivot = reinterpret_cast<char*>(memory);

	return;
}