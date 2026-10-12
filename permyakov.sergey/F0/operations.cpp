#ifndef OPERATIONS.CPP
#define OPERATIONS.CPP
#include "operations.hpp"

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
    spc_t spaces = man.getSpaces();
    evn_t source();
    std::string s, e;
    for(size_t i = 0; i < n; ++i) {
      if(in >> s >> e) {
        float chance = spaces.get(s).get(e);
        if (chance < 0 || chance > 1) {
          std::invalid_argument("expected chance from 0 to 1");
        }
        if (source.has(s)) {
          source.get(s) += chance;
          if(source.get(s) > 1) {
            std::out_of_range("sum events in one space bigger than 1");
          }
        } else {
          source.add(s, chance);
        }
      } else {
        std::invalid_argument("expected:<space-nameX> <event-nameX>");
      }
    }
    permyakov::RobinIter< std::string, float > it(source);
    float sum = (*it).second();
    while(hasNext(it)) {
      it++;
      sum *= (*it).second();
    }
    evn_t events();
    events.add("true", sum);
    events.add("false", 1 - sum);
    if(spaces.has(name)) {
      spaces.drop(name);
    }
    spaces.add(name, events);
    man.saveToFile();
  } else {
    std::invalid_argument("expected:<space-name> <count>");
  }
}

void permyakov::multi(std::ostream & in, permyakov::Manager & man) {
  std::string name;
  size_t n;
  if (in >> name >> n) {
    spc_t spaces = man.getSpaces();
    float mul = 1;
    std::string s, e;
    for(size_t i = 0; i < n; ++i) {
      if(in >> s >> e) {
        float chance = spaces.get(s).get(e);
        if (chance < 0 || chance > 1) {
          std::invalid_argument("expected chance from 0 to 1");
        }
        mul *= chance;
      } else {
        std::invalid_argument("expected:<space-nameX> <event-nameX>");
      }
    }
    evn_t events();
    events.add("true", mul);
    events.add("false", 1 - mul);
    if(spaces.has(name)) {
      spaces.drop(name);
    }
    spaces.add(name, events);
    man.saveToFile();
  } else {
    std::invalid_argument("expected:<space-name> <count>");
  }
}

void permyakov::make(std::ostream & in, permyakov::Manager & man) {
  std::string name;
  size_t n;
  if (in >> name >> n) {
    evn_t events();
    std::string e;
    float chance;
    for(size_t i = 0; i < n; ++i) {
      if(in >> e >> chance) {
        if (chance < 0 || chance > 1) {
          std::invalid_argument("expected chance from 0 to 1");
        }
        events.add(e, chance);
      } else {
        std::invalid_argument("expected:<event-nameX> <chanceX>");
      }
    }
    permyakov::RobinIter< std::string, float > it(events);
    float sum = (*it).second();
    while(hasNext(it)) {
      it++;
      sum += (*it).second();
    }
    if(sum > 1) {
      std::out_of_range("sum events in one space bigger than 1");
    } else if (sum < 1) {
      events.add("none", 1 - sum);
    }
    spc_t spaces = man.getSpaces();
    if(spaces.has(name)) {
      spaces.drop(name);
    }
    spaces.add(name, events);
    man.saveToFile();
  } else {
    std::invalid_argument("expected:<space-name> <count>");
  }
}

void permyakov::construct(std::ostream & in, permyakov::Manager & man) {
  std::string name;
  size_t n;
  if (in >> name >> n) {
    spc_t spaces = man.getSpaces();
    evn_t events();
    std::string s;
    for(size_t i = 0; i < n; ++i) {
      if(in >> s) {
        float chance spaces.get(s).get("true");
        if (chance < 0 || chance > 1) {
          std::invalid_argument("expected chance from 0 to 1");
        }
        events.add(s, chance);
      } else {
        std::invalid_argument("expected:<bin-space-nameX>");
      }
    }
    permyakov::RobinIter< std::string, float > it(events);
    float sum = (*it).second();
    while(hasNext(it)) {
      it++;
      sum += (*it).second();
    }
    if(sum > 1) {
      std::out_of_range("sum events in one space bigger than 1");
    } else if (sum < 1) {
      events.add("none", 1 - sum);
    }
    if(spaces.has(name)) {
      spaces.drop(name);
    }
    spaces.add(name, events);
    man.saveToFile();
  } else {
    std::invalid_argument("expected:<space-name> <count>");
  }
}

void permyakov::copy(std::ostream & in, permyakov::Manager & man) {
  std::string name1, name2;
  if (in >> name1 >> name2) {
    spc_t spaces = man.getSpaces();
    float n = spaces.get(name2).get("true");
    evn_t events();
    events.add("true", n);
    events.add("false", 1 - n);
    if(spaces.has(name)) {
      spaces.drop(name);
    }
    spaces.add(name, events);
    man.saveToFile();
  } else {
    std::invalid_argument("expected:<space-name1> <space-name2>");
  }
}

void permyakov::reverse(std::ostream & in, permyakov::Manager & man);
void permyakov::get(std::ostream & in, permyakov::Manager & man);
void permyakov::bayes(std::ostream & in, permyakov::Manager & man);
void permyakov::deleteS(std::ostream & in, permyakov::Manager & man);

#endif