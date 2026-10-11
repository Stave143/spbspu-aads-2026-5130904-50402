#ifndef OPERATIONS.CPP
#define OPERATIONS.CPP
#include "operations.hpp"

bool permyakov::isEventsFromSpace(permyakov::Manager & man, const std::string first, const std::string second) {
  return false;
}

void permyakov::bin(std::ostream & in, permyakov::Manager & man) {
  std::string name;
  float n;
  if (in >> name >> n) {
    if (n < 0 || n > 1) {
      std::invalid_argument("expected chance from 0 to 1");
    }
    spc_t spaces = man.getSpaces();
    evn_t events();
    events.add("true", n);
    events.add("false", 1 - n);
    if(spaces.has(name)) {
      spaces.drop(name);
    }
    spaces.add(name, events);
    man.saveToFile();
  } else {
    std::invalid_argument("expected:<space-name> <chance>");
  }
}

void permyakov::sum(std::ostream & in, permyakov::Manager & man) {
  std::string name;
  size_t n;
  if (in >> name >> n) {
    std::string s;
    size_t chnc;
    for(size_t i = 0; i < n; ++i) {
      spc_t events
      if(in >> s >> chnc) {
        if (chnc < 0 || chnc > 1) {
          std::invalid_argument("expected chance from 0 to 1");
        }

      } else {
        std::invalid_argument("expected:<space-nameX> <event-nameX>");
      }
    }
  } else {
    std::invalid_argument("expected:<space-name> <count>");
  }
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