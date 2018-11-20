
//
#include <iostream>
#include "MemoryManager.h"


struct ss
{
	ss(int t)
	{
		std::cout << "ss constructor" << std::endl;
		i = t;
		b = 'c';
		l = 434343434;
		s = new char[10];
	}

	~ss()
	{
		delete s;
	}
	int i;
	char b;
	long long l;
	char * s;
};

int main()
{

	MemoryManager::Initialize();

	int *i = new int[20];

	std::unique_ptr<ss> s = std::make_unique<ss>(58);

	MemoryManager::dump(10);



	delete[] i;

	//MemoryPool pool;
	//ss s;
	//pool.alloc(sizeof(ss), s);

	//auto sssss = new ss(10);

	//delete sssss;
}