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
  template< class T > class LIter;
  template< class T > class LCIter;
  template< class T > class vector
  {
    explicit vector(size_t k);
    T *data_;
    size_t size_, capasity_;
    public:
      Vector();
      Vector(const Vector< T > &);
      Vector(Vector< T > &&) noexcept;
      explicit Vector(std::initializer_list< T > il);
      Vector< T > & operator=(const Vector< T > &);
      Vector< T > & operator=(Vector< T > &&) noexcept;
      ~Vector();

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
  }
}

#endif