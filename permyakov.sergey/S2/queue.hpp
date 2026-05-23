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
      size_t size_;
  }
}

#endif