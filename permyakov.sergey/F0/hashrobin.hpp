#ifndef HASHROBIN.HPP
#define HASHROBIN.HPP

#include <algorithm>
#include <stdexcept>
#include <utility>
#include <functional>
#include <memory>
#include <cstddef>
#include "hasher.hpp"
#include "vector.hpp"

namespace permyakov
{
  template< class Key, class Value >
  struct RobinNode
  {
    std::pair< Key, Value > value;
    size_t psl;
    bool engaged;
    RobinNode();
    void swap(RobinNode &other);
  };

  template< class Key, class Value, class Hash = permyakov::SipHasher< Key >, class Equal = std::equal_to< Key > >
  class RobinTable
  {
    Vector< RobinNode< Key, Value > > data;
    Hash hasher;
    Equal comparator;
    size_t length;
    size_t elements;
    public:
      RobinTable();
      explicit RobinTable(size_t length);
      RobinTable(std::initializer_list< std::pair< Key, Value > > il);

      bool has(Key k) const noexcept;
      void add(Key k, Value v);
      void drop(Key k);
      Value &get(Key k);
      const Value &get(Key k) const;
      void changeKey(Key from, Key to);
      void rehash(size_t length);

      size_t size() const noexcept;
      bool isEmpty() const noexcept;
      void clear() noexcept;
      void swap(RobinTable &other) noexcept;  
  };
}

template< class Key, class Value >
permyakov::RobinNode< Key, Value >::RobinNode():
  value(),
  psl(0),
  engaged(false)
{}

template< class Key, class Value, class Hash, class Equal >
permyakov::RobinTable< Key, Value, Hash, Equal >::RobinTable(size_t length):
  data(),
  hasher_(Hash{}),
  comparator_(Equal{}),
  length(length),
  elements(0),
{
  data.reserve(length);
  for (size_t i = 0; i < length; ++i) {
    data.pushBack(RobinNode< Key, Value >());
  }
}

template< class Key, class Value, class Hash, class Equal >
permyakov::RobinTable< Key, Value, Hash, Equal >::RobinTable(std::initializer_list< std::pair< Key, Value > > list):
  RobinTable(list.size())
{
  data.reserve(list.size());
  for (const std::pair< Key, Value > & k : list) {
    add(k.first, k.second);
  }
}

template< class Key, class Value, class Hash, class Equal >
permyakov::RobinTable< Key, Value, Hash, Equal >::RobinTable():
  RobinTable(16)
{}

