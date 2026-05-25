#ifndef HASH_HPP
#define HASH_HPP
#include <cstddef>
#include <boost/container_hash/hash.hpp>
#include <boost/hash2/get_integral_result.hpp>
#include <boost/hash2/hash_append.hpp>
#include <boost/hash2/siphash.hpp>

namespace permyakov
{
  template< class T, clash H = boost::hash2::siphash_64 > struct sipHash
  {
    size_t operator()(const T & value) const;
  };
  template< class T > struct pairSipHash
  {
    size_t operator()(const std::pair< T, T > & s) const;
  };
}

template< class T, class H > size_t permyakov::sipHash< T, H >::operator()(const T &value) const
{
  H hasher{};
  boost::hash2::hash_append(hasher, {}, value);
  return boost::hash2::get_integral_result< size_t >(hasher);
}

template< class T > size_t permyakov::pairSipHash< T >::operator()(const std::pair< T, T > & s) const
{
  size_t hash = permyakov::sipHash< T >{}(s.first);
  boost::hash_combine(hash, permyakov::sipHash< T >{}(s.second));
  return hash;
}

#endif
