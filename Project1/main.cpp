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

	system("pause");
	return 0;
}