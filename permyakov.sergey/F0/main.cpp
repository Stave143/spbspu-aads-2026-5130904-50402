#include <iostream>
#include <limits>
#include "manager.hpp"

int main()
{ 
  using cmd_t = void(*)(std::ostream &, std::istream &, );
  permyakov::RobinTable< std::string, cmd_t> cmds(10);
  
  cmds.add("bin", permyakov::bin);
  cmds.add("sum", permyakov::sum);
  cmds.add("multi", permyakov::multi);
  cmds.add("make", permyakov::make);
  cmds.add("construct", permyakov::construct);
  cmds.add("copy", permyakov::copy);
  cmds.add("reverse", permyakov::reverse);
  cmds.add("get", permyakov::get);
  cmds.add("bayes", permyakov::bayes);
  cmds.add("delete", permyakov::deleteS);

  while (std::cin >> cmd) {
    try {
      if (std::cin.fail()) {
        std::cin.clear(std::cin.rdstate() & ~std::ios::failbit);
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
      cmds.get(cmd)(std::cin, std::cout, "spaces.txt");
      std::cout << '\n';
    } catch (const std::exception &e) {
      std::cout << e.what() << '\n';
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}