#ifndef OPERATIONS.CPP
#define OPERATIONS.CPP
#include "operations.hpp"

void permyakov::bin(std::ostream & in, permyakov::Manager & man) {
  std::string s;
  float n;
  if (in >> s >> n) {
    if (n < 0 || n > 1) {
      std::invalid_argument("expected chance from 0 to 1");
    }
    spc_t spaces = man.getSpaces();
    evn_t events();
    events.add("true", n);
    events.add("false", 1 - n);
    if(spaces.has(s)) {
      spaces.drop(s);
    }
    spaces.add(s, events);
    man.saveToFile();
  } else {
    std::invalid_argument("expected:<space-name> <chance>");
  }
}

void permyakov::sum(std::ostream & in, permyakov::Manager & man) {
  
}

void permyakov::multi(std::ostream & in, permyakov::Manager & man);
void permyakov::make(std::ostream & in, permyakov::Manager & man);
void permyakov::construct(std::ostream & in, permyakov::Manager & man);
void permyakov::copy(std::ostream & in, permyakov::Manager & man);
void permyakov::reverse(std::ostream & in, permyakov::Manager & man);
void permyakov::get(std::ostream & in, permyakov::Manager & man);
void permyakov::bayes(std::ostream & in, permyakov::Manager & man);
void permyakov::deleteS(std::ostream & in, permyakov::Manager & man);

#endif