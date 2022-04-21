#pragma once

#include "time.h"


template <typename T>
void TestMemoryPool(T&& t, int num)
{
	clock_t start, end;
	int allocTime;
	int freeTime;

	MemoryPool<T>* memoryPool = new MemoryPool<T>(num);

	vector<void*> v;

	start = clock();
	for (int i = 0; i < num; ++i)
	{
		void* memory = memoryPool->Alloc(sizeof(T)-sizeof(char*));
		v.push_back(memory);
	}
	end = clock();

	allocTime = end - start;

	start = clock();
	for (auto& v : v)
	{
		memoryPool->Free(v);
	}
	end = clock();

	freeTime = end - start;

	printf("�޸� Ǯ ��� �� %d, Alloc �ð� : %d ms \n", num, allocTime);
	printf("�޸� Ǯ ��� �� %d, Free �ð� : %d ms \n\n", num, freeTime);

	delete memoryPool;
}

template <typename T>
void TestHeap(T&& t, int num)
{
	clock_t start, end;
	int allocTime;
	int freeTime;

	vector<T*> v2;
	start = clock();
	for (int i = 0; i < num; ++i)
	{
		auto* memory = new T;
		v2.push_back(memory);
	}
	end = clock();

	allocTime = end - start;

	start = clock();
	for (auto& v2 : v2)
	{
		delete v2;
	}
	end = clock();

	freeTime = end - start;

	printf("\n�� ��� �� %d, Alloc �ð� : %d ms \n", num, allocTime);
	printf("�� ��� �� %d, Free �ð� : %d ms \n\n", num, freeTime);
}
