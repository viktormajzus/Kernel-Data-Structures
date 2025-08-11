#pragma once
#include "alloc.hpp"

inline void* operator new(size_t, void* ptr) noexcept
{
  return ptr;
}
inline void operator delete(void*, void*) noexcept
{

}


namespace kds
{
  template<typename T>
  class LinkedList
  {
  private:
    struct Node
    {
      T data;
      Node* prev{ nullptr };
      Node* next{ nullptr };

      Node(const T& data)
        : data(data)
      {

      }
    };

    Node* head{ nullptr };
    Node* tail{ nullptr };
    size_t size{};
    kds::allocator<Node> alloc;

  public:
    explicit LinkedList(ULONG tag = 'KDLS', ULONG flags = POOL_FLAG_NON_PAGED)
      : alloc(tag, flags)
    {

    }
    ~LinkedList()
    {
      clear();
    }

    LinkedList(const LinkedList& other)
      : head{ nullptr }, tail{ nullptr }, size{ 0 }
    {
      for (Node* current = other.head; current; current = current->next)
        push_back(current->data);
    }

    LinkedList& operator=(const LinkedList& other)
    {
      if (this == &other)
        return *this;

      clear();
      for (Node* current = other.head; current; current = current->next)
        push_back(current->data);

      return *this;
    }

    LinkedList(LinkedList&& other) noexcept
      : head(other.head), tail(other.tail), size(other.size)
    {
      other.head = other.tail = nullptr;
      other.size = 0;
    }

    LinkedList& operator=(LinkedList&& other) noexcept
    {
      if (this == &other) return *this;
      clear();
      head = other.head; tail = other.tail; size = other.size;
      other.head = other.tail = nullptr; other.size = 0;
      return *this;
    }


    template<typename Func>
    void for_each_forward(Func&& func)
    {
      Node* current{ head };
      while (current)
      {
        func(current->data);
        current = current->next;
      }
    }

    template<typename Func>
    void for_each_backward(Func&& func)
    {
      Node* current{ tail };
      while (current)
      {
        func(current->data);
        current = current->prev;
      }
    }

    T* at(size_t index)
    {
      if (index >= size)
        return nullptr;

      if (index < (getSize() / 2))
      {
        size_t i{ 0 };
        Node* current{ head };
        while (i++ < index)
        {
          current = current->next;
        }

        return &current->data;
      }
      else
      {
        size_t i{ getSize() - 1 };
        Node* current{ tail };
        while (i-- > index)
        {
          current = current->prev;
        }

        return &current->data;
      }
    }

    /// UNSAFE
    /// Out of bounds will result in BSOD
    T& operator[](size_t index)
    {
      NT_ASSERT(index < getSize());

      return *this->at(index);
    }

    void push_front(const T& value)
    {
      Node* ptr{ alloc.allocate(1) };
      if (!ptr)
        return;

      new(ptr) Node(value);

      ptr->next = head;
      ptr->prev = nullptr;

      if (head != nullptr)
        head->prev = ptr;
      else
        tail = ptr;

      head = ptr;
      ++size;
    }
    void push_back(const T& value)
    {
      Node* ptr{ alloc.allocate(1) };
      new(ptr) Node(value);
      ptr->next = nullptr;
      ptr->prev = tail;

      if (tail)
        tail->next = ptr;
      else
        head = ptr;

      tail = ptr;
      ++size;
    }

    void pop_front()
    {
      if (!head)
        return;

      Node* current{ head };
      if (current->next)
      {
        head = current->next;
        current->next->prev = nullptr;
      }
      else
      {
        tail = nullptr;
        head = nullptr;
      }

      current->~Node();
      alloc.deallocate(current, 1);
      --size;
    }

    void pop_back()
    {
      if (!tail)
        return;

      Node* current{ tail };
      if (current->prev)
      {
        tail = current->prev;
        current->prev->next = nullptr;
      }
      else
      {
        head = nullptr;
        tail = nullptr;
      }

      current->~Node();
      alloc.deallocate(current, 1);
      --size;
    }

    T* front()
    {
      return (head ? &head->data : nullptr);
    }
    T* back()
    {
      return (tail ? &tail->data : nullptr);
    }

    const T* front() const
    {
      return (head ? &head->data : nullptr);
    }
    const T* back() const
    {
      return (tail ? &tail->data : nullptr);
    }

    void clear() noexcept
    {
      if (!tail)
      {
        head = nullptr;
        size = 0;

        return;
      }

      Node* current{ tail };
      while (current)
      {
        Node* temp{ current };
        current = current->prev;

        temp->~Node();
        alloc.deallocate(temp, 1);
      }

      head = nullptr;
      tail = nullptr;
      size = 0;
    }

    bool empty() const
    {
      return size == 0;
    }

    size_t getSize() const
    {
      return size;
    }
  };
}