#pragma once

namespace kds
{
  template<typename T>
  class vector
  {
  private:
    size_t m_size;
    T* m_arrPtr;
    size_t m_reservedSize;

  public:
    Vector();
    explicit Vector(size_t size);
    ~Vector();

  public:
    void reserve(size_t size);
    T* at(size_t index);
    const T* at(size_t index) const;
    void clear();
    bool empty() const;
  };



  // -----------------------------
  // Implementations
  // -----------------------------

  template<typename T>
  inline void vector<T>::reserve(const size_t size)
  {
  }
}
