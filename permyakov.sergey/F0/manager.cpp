#ifndef MANAGER.CPP
#define MANAGER.CPP
#include "manager.hpp"

void permyakov::Manager::parseLine(std::string line) {
  std::istringstream iline(line);
  std::string name;
  size_t size;
  iline >> name >> size;
  evn_t events(size);
  std::string s;
  float n;
  while (iline >> s) {
    if(iline >> n) {
      events.add(s, n);
    } else {
      std::invalid_argument("Сorrupted file");
    }
  }
  spaces.add(name, events);
}

spc_t permyakov::Manager::getSpaces() {
  return spaces;
}

void permyakov::Manager::loadFile() {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::invalid_argument("None filename");
  }
  std::string line;
  size_t lineNumber = 0;
  while (std::getline(file, line)) {
    ++lineNumber;
    if (line.empty()) {
      continue;
    } else if (line.back() == '\r') {
      line.pop_back();
    }
    parseLine(line);
  }
}

void permyakov::Manager::saveToFile()
{
  std::ofstream file(outputFilename);
  if (!file.is_open()) {
    throw std::invalid_argument("None filename");
  }
  permyakov::RobinIter < std::string, evn_t > itS(spaces);
  while(itS.hasNext()) {
    std::pair< std::string, evn_t > line = *itS;
    file << line.first() << ' ' << line.second().size();
    permyakov::RobinIter < std::string, evn_t > itE(line.second());
    while(itE.hasNext()) {
      std::pair< std::string, evn_t > event = *itE;
      file << ' ' << line.first() << ' ' << line.first().size();
    }
    file << '\n';
  }
}

#endif