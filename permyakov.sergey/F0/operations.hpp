#ifndef OPERATIONS.HPP
#define OPERATIONS.HPP
#include "manager.hpp"

namespace permyakov
{
  void bin(std::ostream & in, permyakov::Manager & man);
  void sum(std::ostream & in, permyakov::Manager & man);
  void multi(std::ostream & in, permyakov::Manager & man);
  void make(std::ostream & in, permyakov::Manager & man);
  void construct(std::ostream & in, permyakov::Manager & man);
  void copy(std::ostream & in, permyakov::Manager & man);
  void reverse(std::ostream & in, permyakov::Manager & man);
  void get(std::ostream & in, permyakov::Manager & man);
  void bayes(std::ostream & in, permyakov::Manager & man);
  void deleteS(std::ostream & in, permyakov::Manager & man);
  void deleteE(std::ostream & in, permyakov::Manager & man);
}

#endif