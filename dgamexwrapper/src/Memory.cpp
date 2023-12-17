#include <new>
#include "dgamex86.h"


//
//// no inline, required by [replacement.functions]/3
//void* operator new(std::size_t s)
//{
//    int* p;
//
//    if (s == 0)
//        throw std::bad_alloc{};
//
//    s += sizeof(int);
//    p = (int*)gi->Malloc(s);
//    if (!p)
//        throw std::bad_alloc{};
//    *p = s;
//    return p + 1;
//}
//
//// no inline, required by [replacement.functions]/3
//void* operator new[](std::size_t s)
//{
//    int* p;
//
//    if (s == 0)
//        throw std::bad_alloc{};
//
//    s += sizeof(int);
//    p = (int*)gi->Malloc(s);
//    if (!p)
//        throw std::bad_alloc{};
//    *p = s;
//    return p + 1;
//}
//
//void operator delete(void* ptr) noexcept
//{
//    int* p;
//    p = ((int*)ptr) - 1;
//    gi->Free(p);
//}
//
//void operator delete(void* ptr, std::size_t size) noexcept
//{
//    int* p;
//    p = ((int*)ptr) - 1;
//    gi->Free(p);
//}
//
//void operator delete[](void* ptr) noexcept
//{
//    int* p;
//    p = ((int*)ptr) - 1;
//    gi->Free(p);
//}
//
//void operator delete[](void* ptr, std::size_t size) noexcept
//{
//    int* p;
//    p = ((int*)ptr) - 1;
//    gi->Free(p);
//}