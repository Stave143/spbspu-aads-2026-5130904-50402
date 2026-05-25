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
      T & at(size_t id);
      const T & at(size_t id) const;

      bool isEmpty() const noexcept;
      size_t size() const noexcept;
      size_t capasity() const noexcept;

      void reserve(size_t cap);
      void swap(Vector< T > &rhs) noexcept;

      void pushFront(const T &);
      void popFront();
      void pushBack(const T &);
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
}

  template< class T > permyakov::Vector< T >::Vector():
    data_(nullptr),
    size_(0),
    capasity_(0)
  {}

  template< class T > permyakov::Vector< T >::Vector(size_t k):
    data_(static_cast< T * >(::operator new(sizeof(T) * k))),
    size_(0),
    capasity_(k)
  {}

  template< class T > permyakov::Vector< T >::Vector(const Vector< T > & scnd):
    Vector(scnd.size())
  {
    while (size_ < scnd.size()) {
      new (data_ + size_) T(scnd[size_]);
      ++size_;
    }
  }

  template< class T > permyakov::Vector< T >::Vector(Vector< T > && scnd) noexcept:
    data_(scnd.data_),
    size_(scnd.size_),
    capasity_(scnd.capasity_)
  {
    scnd.data_ = nullptr;
    scnd.size_ = 0;
    scnd.capasity_ = 0;
  }

  template< class T > permyakov::Vector< T > & permyakov::Vector< T >::operator=(const Vector< T > & scnd)
  {
    if (this == std::addressof(scnd)) {
      return *this;
    }
    Vector< T > copy(scnd);
    swap(copy);
    return *this;
  }

  template< class T > permyakov::Vector< T > & permyakov::Vector< T >::operator=(Vector< T > && scnd) noexcept
  {
    if (this == std::addressof(scnd)) {
      return *this;
    }
    Vector< T > copy(std::move(scnd));
    swap(copy);
    return *this;
  }

  template< class T > permyakov::Vector< T >::~Vector()
  {
    clear(date_, size_);
  }

  template< class T > permyakov::Vector< T >::Vector(std::initializer_list< T > il):
    Vector(il.size())
  {
    for (auto && v : il) {
      new (data_ + size_++) T(std::move(v));
    } 
  }

#endif