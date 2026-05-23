#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "iterators.hpp"

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
  }

  template< class T > void queue< T >::push(const T value)
  {
    LIter< T > endIter = date.end();
    date.push_back(endIter, value);
  }

  template< class T > void queue< T > ::pop()
  {
    LIter< T > iter = date.begin();
    for (size_t i = 1; i < date.size(); ++i) {
      ++iter;
    }
    date.erase_after(iter);
  }
}

#endif