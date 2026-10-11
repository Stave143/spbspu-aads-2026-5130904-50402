#ifndef MANAGER.HPP
#define MANAGER.HPP
#include <iosfwd>
#include <fstream>
#include <sstream>
#include <string>
#include "hashrobin.hpp"

namespace permyakov
{
  using evn_t = RobinTable< std::string, float >;
  using spc_t = RobinTable< std::string, evn_t >;

  class Manager
  {
    std::string filename;
    spc_t spaces;

    Manager(std::string file, spc_t empTble):
      filename(file),
      spaces(empTble)
    {}

    void parseLine(std::string line);

    public:
      void loadFile();
  };
}

#endif