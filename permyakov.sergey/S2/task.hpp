#ifndef CALCULATE_HPP
#define CALCULATE_HPP
#include <string>
#include <iosfwd>
#include <iostream>
#include "queue.hpp"

namespace permyakov
{
  Queue< Queue< std::string > > input(std::istream & is);
  void output(std::ostream & out, Queue< long long > que);
}

#endif