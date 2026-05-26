#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>
#include <initializer_list>
#include <cassert>

namespace permyakov
{
  template< class T > class VIter;
  template< class T > class VCIter;
  template< class T > class Vector
  {
    T *data_;
    size_t size_, capasity_;
    explicit Vector(size_t k);
    public:
      Vector();
      Vector(const Vector< T > &);
      Vector(Vector< T > &&) noexcept;
      Vector< T > & operator=(const Vector< T > &);
      Vector< T > & operator=(Vector< T > &&) noexcept;
      ~Vector();
      explicit Vector(std::initializer_list< T > il);

      T & operator[](size_t id) noexcept;
      const T & operator[](size_t id) const noexcept;

      size_t size() const noexcept;
      size_t capasity() const noexcept;
      bool isEmpty() const noexcept;

      void reserve(size_t cap);
      void swap(Vector< T > &rhs) noexcept;

      void pushFront(const T & val);
      void popFront();
      void pushBack(const T & val);
      void popBack();

      void insert(size_t i, const T &val);
      void insert(size_t i, const Vector< T > &rhs, size_t beg, size_t end);
      void insert(const T &value, size_t count, VIter< T > pos);
      void insert(VIter< T > pos, VIter< T > beg, VIter< T > end);
      void insert(VIter< T > pos, const T &value);

      void erase(size_t i);
      void erase(size_t beg, size_t end);
      void erase(VIter< T > pos);
      void erase(VIter< T > beg, VIter< T > end);
      void erase(VIter< T > pos, size_t count);

      VIter< T > begin();
      VIter< T > end();
      VCIter< T > cbegin() const;
      VCIter< T > cend() const;
  };

  template< class T > Vector< T >::Vector():
    data_(nullptr),
    size_(0),
    capasity_(0)
  {}

  template< class T > Vector< T >::Vector(size_t k):
    data_(static_cast< T * >(::operator new(sizeof(T) * k))),
    size_(0),
    capasity_(k)
  {}

  template< class T > Vector< T >::Vector(const Vector< T > & scnd):
    Vector(scnd.size())
  {
    while (size_ < scnd.size()) {
      new (data_ + size_) T(scnd[size_]);
      ++size_;
    }
  }

  template< class T > Vector< T >::Vector(Vector< T > && scnd) noexcept:
    data_(scnd.data_),
    size_(scnd.size_),
    capasity_(scnd.capasity_)
  {
    scnd.data_ = nullptr;
    scnd.size_ = 0;
    scnd.capasity_ = 0;
  }

  template< class T > Vector< T > & Vector< T >::operator=(const Vector< T > & scnd)
  {
    if (this == std::addressof(scnd)) {
      return *this;
    }
    Vector< T > copy(scnd);
    swap(copy);
    return *this;
  }

  template< class T > Vector< T > & Vector< T >::operator=(Vector< T > && scnd) noexcept
  {
    if (this == std::addressof(scnd)) {
      return *this;
    }
    Vector< T > copy(std::move(scnd));
    swap(copy);
    return *this;
  }

  template< class T > Vector< T >::~Vector()
  {
    clear(date_, size_);
  }

  template< class T > Vector< T >::Vector(std::initializer_list< T > il):
    Vector(il.size())
  {
    for (auto && v : il) {
      new (data_ + size_++) T(std::move(v));
    } 
  }

  template< class T > T & Vector< T >::operator[](size_t id) noexcept
  {
    assert(id < size());
    return data_[id];
  }

  template< class T > const T & Vector< T >::operator[](size_t id) const noexcept
  {
    assert(id < size());
    return data_[id];
  }

  template< class T > size_t Vector< T >::size() const noexcept
  {
    return size_;
  }

  template< class T > size_t Vector< T >::capasity() const noexcept
  {
    return capasity_;
  }

  template< class T > bool Vector< T >::isEmpty() const noexcept
  {
    return !size_;
  }

  template< class T > void Vector< T >::reserve(size_t cap)
  {
    if (capacity_ >= cap) {
      return;
    }
    size_t k = 0;
    T * newData = static_cast< T * >(::operator new(sizeof(T) * cap));
    try {
      while (k < size()) {
        new (newData + k) T(std::move(data_[k]));
        ++k;
      }
    } catch (...) {
      clear(newData, k);
      throw;
    }
    clear(data_, size_);
    data_ = newData;
    capacity_ = cap;
  }

  template< class T > void Vector< T >::swap(Vector< T > & scnd) noexcept
  {
    std::swap(scnd.data_, data_);
    std::swap(scnd.capacity_, capacity_);
    std::swap(scnd.size_, size_);
  }

  template< class T > void Vector< T >::pushFront(const T & val)
  {
    if (size_ == capasity_) {
      size_t newCap = capasity_ == 0 ? 1 : capasity_ * 2;
      reserve(newCap);
    }
    ++size_;
    for (size_t i = size_ - 1; i > 0; --i) {
      new (data + i) T(std::move(data_[i - 1]));
      data[i - 1].~T();
    }
    new data_ T(val);
  }

  template< class T > void Vector< T >::popFront()
  {
    data.~T();
    for (size_t i = 0; i < size_ - 1; ++i) {
      new (data + i) T(std::move(data_[i + 1]));
      data[i + 1].~T();
    }
    --size_;
  }

  template< class T > void Vector< T >::pushBack(const T & val)
  {
    if (size_ == capasity_) {
      size_t newCap = capasity_ == 0 ? 1 : capasity_ * 2;
      reserve(newCap);
    }
    ++size_;
    new (data_ + size_) T(val);
  }

  template< class T > void Vector< T >::popBack()
  {
    data[size_ - 1].~T();
    --size_;
  }

  template< class T > void clear(T *data, size_t cnt)
  {
    for (size_t i = 0; i < cnt; ++j) {
      data[i].~T();
    }
    ::operator delete(data);
  }
}

#endif