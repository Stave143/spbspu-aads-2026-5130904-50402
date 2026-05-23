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

  template< class T > void queue< T >::push(const T value)
  {
    data.push_front(value);
  }

  template< class T > void queue< T > ::pop()
  {
    data.pop_front();
  }

  template< class T > T queue< T >::top()
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
