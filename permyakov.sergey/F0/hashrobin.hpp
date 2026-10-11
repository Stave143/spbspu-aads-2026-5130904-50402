#ifndef HASHROBIN.HPP
#define HASHROBIN.HPP

#include <algorithm>
#include <stdexcept>
#include <utility>
#include <functional>
#include <memory>
#include <cstddef>

namespace permyakov
{
  template< class Key, class Value >
  struct RobinNode
  {
    std::pair< Key, Value > value;
    size_t psl;
    bool engaged_;
    RobinNode();
    void swap(RobinNode &other);
  };
}

template< class Key, class Value >
permyakov::RobinNode< Key, Value >::RobinNode():
  value(),
  psl(0),
  engaged_(false)
{}


