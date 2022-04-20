#include <iostream>
#include <vector>
#include "time.h"

#include "MemoryPool.h"
#include "TestTemplate.h"

using namespace std;

class TestClass
{
public:
	int x;
	int y;

	void Print()
	{
		if (this == nullptr) return;

		cout << "x : " << x << ", y : " << y << endl;
	}
};

int main(void)
{
	int num = 256*256*256;

	TestHeap(FMemoryBlock64(), num);
	TestMemoryPool(FMemoryBlock64(), num);

	MemoryPool<FMemoryBlock64>* memoryPool = new MemoryPool<FMemoryBlock64>(5);

	vector<TestClass*> v1;
	for (int i = 0; i < 5; ++i)
	{
		auto test = reinterpret_cast<TestClass*>(memoryPool->Alloc());
		test->x = i;
		test->y = -i;
		v1.push_back(test);
	}

	for (const auto& v : v1)
	{
		v->Print();
		memoryPool->Free(v);
	}

	v1.clear();

	for (int i = 0; i < 5; ++i)
	{
		auto test = reinterpret_cast<TestClass*>(memoryPool->Alloc());
		v1.push_back(test);
	}

	for (const auto& v : v1)
	{
		v->Print();
		memoryPool->Free(v);
	}


	system("pause");
	return 0;
}