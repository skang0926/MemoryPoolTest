#include <iostream>
#include "MemoryPool.h"
#include "time.h"


using namespace std;


int main(void)
{
	int num = 256*256*256;
	clock_t start, end;
	int allocTime;
	int freeTime;
	MemoryPool* memoryPool = new MemoryPool(num);	

	vector<FMemoryBlock*> v2;


	start = clock();
	for (int i = 0; i < num; ++i)
	{
		FMemoryBlock* memory = new FMemoryBlock;
		v2.push_back(memory);
	}
	end = clock();

	allocTime = (double)end - start;
	
	start = clock();
	for (auto& v2 : v2)
	{
		delete v2;
	}
	end = clock();

	freeTime = (double)end - start;

	printf("�� ��� �� %d, Alloc �ð� : %d ms \n", num, allocTime);
	printf("�� ��� �� %d, Free �ð� : %d ms \n\n", num, freeTime);


	vector<void*> v;

	start = clock();
	for (int i = 0; i < num; ++i)
	{
		void* memory = memoryPool->Alloc();
		v.push_back(memory);
	}
	end = clock();

	allocTime = (double)end - start;

	start = clock();
	for (auto& v : v)
	{
		memoryPool->Free(v);
	}
	end = clock();

	freeTime = (double)end - start;

	printf("�޸� Ǯ ��� �� %d, Alloc �ð� : %d ms \n", num, allocTime);
	printf("�޸� Ǯ ��� �� %d, Free �ð� : %d ms \n\n", num, freeTime);


	delete memoryPool;
	system("pause");
		
	return 0;
}