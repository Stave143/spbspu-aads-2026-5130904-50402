#ifndef MANAGER.HPP
#define MANAGER.HPP
#include <iosfwd>
#include <fstream>
#include <sstream>
#include <string>
#include "hashrobin.hpp"

using evn_t = permyakov::RobinTable< std::string, float >;
using spc_t = permyakov::RobinTable< std::string, evn_t >;
using src_t = permyakov::RobinTable< permyakov::RobinTable< std::string, std::string > >;

namespace permyakov
{
  class Manager
  {
    const std::string filename;
    spc_t spaces;
    src_t source;
    std::istream & output;

    Manager(const std::string file, spc_t empTble, std::istream & out):
      filename(file),
      spaces(empTble),
      output(out)
    {}

    void parseLine(std::string line);

    public:
      std::istream & getOutput();
      spc_t & getSpaces();
      src_t getSource();
      void loadFile();
      void saveToFile();
  };
}

#endif