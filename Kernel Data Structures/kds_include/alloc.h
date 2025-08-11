#pragma once
#include <ntddk.h>

#define TAG_UTILS 'KDUT'


//  // new overrides
//  inline void* __cdecl operator new(size_t size)
//  {
//    return ExAllocatePool2(POOL_FLAG_NON_PAGED, size, TAG_UTILS);
//  }
//
//  inline void* __cdecl operator new[](size_t size)
//  {
//    return ExAllocatePool2(POOL_FLAG_NON_PAGED, size, TAG_UTILS);
//  }
//
//  // delete overrides
//  inline void __cdecl operator delete(void* ptr) noexcept
//  {
//    if (ptr)
//      ExFreePool(ptr);
//  }
//
//  inline void __cdecl operator delete[](void* ptr) noexcept
//  {
//    if (ptr)
//      ExFreePool(ptr);
//  }
//
//  // sized delete overrides for C++14+
//#if __cplusplus >= 201402L
//
//  inline void operator delete(void* ptr, size_t) noexcept
//  {
//    if (ptr)
//      ExFreePool(ptr);
//  }
//
//  inline void operator delete[](void* ptr, size_t) noexcept
//  {
//    if (ptr)
//      ExFreePool(ptr);
//  }
//
//#endif

namespace kds
{
  template<class T>
  struct allocator
  {
  private:
    ULONG tag_;
    ULONG flags_;
  public:
    allocator(ULONG tag = 'KDUT', ULONG flags = POOL_FLAG_NON_PAGED)
      : tag_{ tag }, flags_{ flags }
    {

    }

    T* allocate(size_t n)
    {
      if (n > MAXSIZE_T / sizeof(T) || n == 0)
        return nullptr;

      return static_cast<T*>(ExAllocatePool2(flags_, n * sizeof(T), tag_));
    }

    void deallocate(T* p, size_t) noexcept
    {
      if (p)
        ExFreePool(p);
    }
  };
}