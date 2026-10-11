#ifndef MANAGER.HPP
#define MANAGER.HPP
#include <iosfwd>
#include <fstream>
#include <sstream>
#include <string>
#include "hashrobin.hpp"

using evn_t = permyakov::RobinTable< std::string, float >;
using spc_t = permyakov::RobinTable< std::string, evn_t >;

namespace permyakov
{
  class Manager
  {
    std::string filename;
    spc_t spaces;
    std::istream & output;

    Manager(std::string file, spc_t empTble, std::istream & out):
      filename(file),
      spaces(empTble),
      output(out)
    {}

    void parseLine(std::string line);

    public:
      spc_t getSpaces();
      void loadFile();
      void saveToFile();
  };
}

#endif