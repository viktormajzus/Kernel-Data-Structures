#pragma once
#include "alloc.h"

namespace kds
{
  template<typename T>
  class vector
  {
  private:
    size_t m_size{ 0 };
    T* m_arrPtr{ nullptr };
    size_t m_capacity{ 0 };
    kds::allocator<T> m_alloc;

  public:
    explicit vector(ULONG tag = 'KDLS', ULONG flags = POOL_FLAG_NON_PAGED) noexcept;
    explicit vector(size_t size, ULONG tag = 'KDLS', ULONG flags = POOL_FLAG_NON_PAGED) noexcept;
    ~vector();

    // Copy & move
    vector(const vector& other) = delete;
    vector& operator=(const vector& other) = delete;
    vector(vector&& other) noexcept = delete;
    vector& operator=(const vector&& other) noexcept = delete;

  public:
    // 
    T* data() noexcept;
    const T* data() const noexcept;
    size_t size() const noexcept;
    size_t capacity() const noexcept;
    bool empty() const noexcept;

    // Access functions
    T* at(size_t index) noexcept;
    const T* at(size_t index) const noexcept;
    T* front() noexcept;
    const T* front() const noexcept;
    T* back() noexcept;
    const T* back() const noexcept;

    /// Unsafe, no bound checks
    T& operator[](size_t index) noexcept;

    // Operation functions
    bool push_back(const T& value) noexcept;
    void pop_back() noexcept;

    // Memory functions
    void clear() noexcept;
    bool reserve(size_t n) noexcept;
    bool shrink_to_fit() noexcept;
  };



  // -----------------------------
  // Implementations
  // -----------------------------


}
