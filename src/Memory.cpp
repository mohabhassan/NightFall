#include <new>
#include "gamex86.h"
void * operator new(std::size_t n) throw(std::bad_alloc)
{
	void *p = MemoryMalloc(n);
	if (!p)
	{
		std::bad_alloc e;
		throw e;
	}
	return p;
}

void operator delete(void * p) throw()
{
	MemoryFree(p);
}

void *operator new[](std::size_t n) throw(std::bad_alloc)
{
	void *p = MemoryMalloc(n);
	if (!p)
	{
		std::bad_alloc e;
		throw e;
	}
	return p;
}
void operator delete[](void *p) throw()
{
	MemoryFree(p);
}