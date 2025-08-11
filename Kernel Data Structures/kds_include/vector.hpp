#pragma once
#include "alloc.hpp"

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

  template<typename T>
  T* vector<T>::data() noexcept
  {
    return m_arrPtr;
  }

  template<typename T>
  const T* vector<T>::data() const noexcept
  {
    return m_arrPtr;
  }

  template<typename T>
  inline size_t vector<T>::size() const noexcept
  {
    return m_size;
  }

  template<typename T>
  inline size_t vector<T>::capacity() const noexcept
  {
    return m_capacity;
  }

  template<typename T>
  inline bool vector<T>::empty() const noexcept
  {
    return (size == 0 ? true : false);
  }

  template<typename T>
  T* vector<T>::at(size_t index) noexcept
  {
    return (index < m_size ? (m_arrPtr + index) : nullptr);
  }

  template<typename T>
  inline const T* vector<T>::at(size_t index) const noexcept
  {
    return (index < m_size ? (m_arrPtr + index) : nullptr);
  }

  template<typename T>
  T* vector<T>::front() noexcept
  {
    return (m_size > 0 ? m_arrPtr : nullptr);
  }

  template<typename T>
  const T* vector<T>::front() const noexcept
  {
    return (m_size > 0 ? m_arrPtr : nullptr);
  }

  template<typename T>
  T* vector<T>::back() noexcept
  {
    return (m_size > 0 ? (m_arrPtr + (m_size - 1)) : nullptr);
  }

  template<typename T>
  const T* vector<T>::back() const noexcept
  {
    return (m_size > 0 ? (m_arrPtr + (m_size - 1)) : nullptr);
  }

  template<typename T>
  T& vector<T>::operator[](size_t index) noexcept
  {
    return m_arrPtr[index];
  }

  template<typename T>
  bool vector<T>::reserve(size_t n) noexcept
  {
    if (n <= m_capacity)
      return true;
    if (n == 0 || n > MAXSIZE_T / sizeof(T))
      return false;

    T* temp{ m_alloc.allocate(n) };
    if (!temp)
      return false;

    if constexpr (__is_trivially_copyable(T))
    {
      if (m_arrPtr && m_size)
        RtlCopyMemory(temp, m_arrPtr, m_size * sizeof(T));
    }
    else
    {
      for (size_t i = 0; i < m_size; ++i)
      {
        ::new (temp + i) T(static_cast<T&&>(m_arrPtr[i]));
        if constexpr (!__is_trivially_destructible(T)) (m_arrPtr + i)->~T();
    }
  }
}
