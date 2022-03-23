#pragma once

#include <map>
#include <unordered_map>
#include <vector>
#include <list>
using namespace std;

struct FMemoryBlock
{
	char buffer[256];
};

class MemoryPool
{
public:
	MemoryPool(int size);
	~MemoryPool();

	void* Alloc();
	void Free(void* memory);

private:
	FMemoryBlock* memoryPool = nullptr;

	list<int> indexList;
	int memoryPoolSize;
};