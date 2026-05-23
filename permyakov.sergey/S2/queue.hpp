#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "iterators.hpp"
#include <cstddef>

namespace permyakov
{
  template< class T > class queue
  {
    void push(const T value);
    void pop();
    T front();
    size_t size();
    bool isEmpty();
    private:
      List< T > data;
  };

  template< class T > void queue< T >::push(const T value)
  {
    LIter< T > endIter = date.end();
    data.insert_after(endIter, value);
  }

  template< class T > void queue< T > ::pop()
  {
    data.pop_front();
  }

  template< class T > T queue< T >::front()
  {
    return data.front();
  }

  template< class T > size_t queue< T >::size()
  {
    return data.size();
  }

  template< class T > bool queue< T >::isEmpty()
  {
    return !size();
  }
}

#endif