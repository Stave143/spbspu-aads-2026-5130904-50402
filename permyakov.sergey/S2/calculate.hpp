#ifndef CALCULATE_HPP
#define CALCULATE_HPP
#include <string>
#include "queue.hpp"

namespace permyakov
{
  size_t getPriority(const std::string elm);

  Queue< std::string > convertToPostfix(Queue< std::string > exc);

  size_t sum(const std::string elm1, const std::string elm2);
  size_t sub(const std::string elm1, const std::string elm2);
  size_t mult(const std::string elm1, const std::string elm2);
  size_t dec(const std::string elm1, const std::string elm2);
  size_t mod(const std::string elm1, const std::string elm2);
  size_t x_or(const std::string elm);
  size_t calclulate(Queue< std::string > exc);
}

#endif