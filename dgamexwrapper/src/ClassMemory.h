#pragma once
#include "dgamex86.h"
#define CLASS_CUSTOM_ALLOCATION                          \
	public:                                              \
	void* operator new(size_t s)                         \
	{                                                    \
		int* p;                                          \
														 \
		if (s == 0)                                      \
		    throw std::bad_alloc{};                      \
														 \
		s += sizeof(int);                                \
		p = (int*)gi->Malloc(s);                          \
		if (!p)                                          \
		    throw std::bad_alloc{};                      \
		*p = s;                                          \
		return p + 1;                                    \
	}                                                    \
	void* operator new[](size_t s)                       \
	{                                                    \
		int* p;                                          \
														 \
		if (s == 0)                                      \
			throw std::bad_alloc{};                      \
														 \
		s += sizeof(int);                                \
		p = (int*)gi->Malloc(s);                          \
		if (!p)                                          \
			throw std::bad_alloc{};                      \
		*p = s;                                          \
		return p + 1;                                    \
	}                                                    \
	void operator delete(void* ptr)                      \
	{                                                    \
	    int* p;                                          \
	    p = ((int*)ptr) - 1;                             \
	    gi->Free(p);                                      \
	}                                                    \
	void operator delete[](void* ptr)                    \
	{                                                    \
		int* p;                                          \
		p = ((int*)ptr) - 1;                             \
		gi->Free(p);                                      \
	}