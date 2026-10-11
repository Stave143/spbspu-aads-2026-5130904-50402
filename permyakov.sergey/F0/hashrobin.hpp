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
      RobinTable(std::initializer_list< std::pair< Key, Value > > list);

      bool has(Key k) const noexcept;
      void add(Key k, Value v);
      void drop(Key k);
      Value & get(Key k);
      const Value & get(Key k) const;
      void changeKey(Key first, Key second);
      void rehash(size_t length);

      size_t size() const noexcept;
      bool isEmpty() const noexcept;
      void clear() noexcept;
      void swap(RobinTable & other) noexcept;  
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

template< class Key, class Value, class Hash, class Equal >
bool permyakov::RobinTable< Key, Value, Hash, Equal >::has(Key k) const noexcept
{
  if (data.isEmpty()) {
    return false;
  }
  size_t i = hasher(k) % length;
  size_t start = i;
  while (data[i].engaged) {
    if (comparator(k, data[i].value.first)) {
      return true;
    }
    i = (i + 1) % length;
    if (i == start) {
      return false;
    }
  }
  return false;
}

template< class Key, class Value, class Hash, class Equal >
void permyakov::RobinTable< Key, Value, Hash, Equal >::add(Key k, Value v)
{
  if (has(k)) {
    get(k) = v;
    return;
  }
  if (elements >= length * max_load_) {
    rehash(!length ? 16 : length * 2);
  }

  size_t i = hasher_(k) % length;
  size_t psl = 0;
  while (data[i].engaged) {
    if (data[i].psl < psl) {
      std::swap(k, data[i].value.first);
      std::swap(v, data[i].value.second);
      std::swap(psl, data[i].psl);
    }
    i = (i + 1) % length;
    ++psl;
  }
  data[i].value = {k, v};
  data[i].psl = psl;
  data[i].engaged = true;
  ++elements;
}

template< class Key, class Value, class Hash, class Equal >
void permyakov::RobinTable< Key, Value, Hash, Equal >::drop(Key k)
{
  if (data.isEmpty()) {
    return;
  }
  if (!has(k)) {
    throw std::invalid_argument("None key");
  }
  size_t i = hasher_(k) % length;
  size_t start = i;
  while (data[i].engaged) {
    if (comparator_(k, data[i].value.first)) {
      size_t cur = i;
      size_t next = (cur + 1) % length;
      while (data[next].engaged && data[next].psl > 0) {
        data[cur].value = std::move(data[next].value);
        data[cur].psl = data[next].psl - 1;
        cur = next;
        next = (next + 1) % length;
      }
      data[cur].engaged = false;
      data[cur].psl = 0;
      --elements;
      return;
    }
    i = (i + 1) % length;
    if (i == start) {
      throw std::invalid_argument("None key");
    }
  }
}
