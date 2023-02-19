#include <new>
#include "dgamex86.h"
/*
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
void* __cdecl operator new[](
	size_t n,
	std::nothrow_t const&
	) noexcept
{

	void *p = MemoryMalloc(n);
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

void operator delete[](void* p, size_t n) throw()
{
	MemoryFree(p);
}
#endif
#*/