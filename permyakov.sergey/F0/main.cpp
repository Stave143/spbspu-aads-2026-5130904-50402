#include <iostream>
#include <string>
#include "operation.hpp"
#include "recording.hpp"

int main(int argc, char* argv[])
{
  if (argc != 1)
  {
    return 1;
  }

  cmds.add("bin", permyakov::binCmd);
  cmds.add("sum", permyakov::sumCmd);
  cmds.add("multi", permyakov::multiCmd);
  cmds.add("make", permyakov::makeCmd);
  cmds.add("construct", permyakov::constructCmd);
  cmds.add("copy", permyakov::copyCmd);
  cmds.add("reverse", permyakov::reverseCmd);
  cmds.add("get", permyakov::getCmd);
  cmds.add("bayes", permyakov::bayesCmd);
  cmds.add("delete", permyakov::deleteCmd);
}