#ifndef STACK_HPP
#define STACK_HPP
#include "iterators.hpp"

namespace permyakov
{
  template< class T > class queue
  {
    void push(const T value);
    void pop();
    T top();
    size_t size();
    bool isEmpty();
    private:
      List< T > data;
  };
}

#endif
