#pragma once
#include <ntddk.h>

#define TAG_UTILS 'KDUT'


  // new overrides
  void* __cdecl operator new(size_t size)
  {
    return ExAllocatePool2(POOL_FLAG_NON_PAGED, size, TAG_UTILS);
  }

  void* __cdecl operator new[](size_t size)
  {
    return ExAllocatePool2(POOL_FLAG_NON_PAGED, size, TAG_UTILS);
  }

  // delete overrides
  void __cdecl operator delete(void* ptr) noexcept
  {
    if (ptr)
      ExFreePool(ptr);
  }

  void __cdecl operator delete[](void* ptr) noexcept
  {
    if (ptr)
      ExFreePool(ptr);
  }

  // sized delete overrides for C++14+
#if __cplusplus >= 20140L

  void operator delete(void* ptr, size_t) noexcept
  {
    if (ptr)
      ExFreePool(ptr);
  }

  void operator delete[](void* ptr, size_t) noexcept
  {
    if (ptr)
      ExFreePool(ptr);
  }

#endif