#pragma once

#include <map>
#include <unordered_map>
#include <vector>
#include <list>
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
	MemoryPool(int size);
	~MemoryPool();

	void* Alloc();
	void Free(void* memory);

private:
	T* memoryPool = nullptr;

	list<int> indexList;
	int memoryPoolSize;
};