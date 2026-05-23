#ifndef CALCULATE_CPP
#define CALCULATE_CPP
#include <stdexcept>
#include <limits>
#include "calculate.hpp"
#include "queue.hpp"
#include "stack.hpp"

namespace permyakov
{
  size_t getPriority(const std::string elm)
  {
    if (elm == "+" || elm == "-") {
      return 1;
    }
    if (elm == "*" || elm == "/" || elm == "%") {
      return 2;
    }
    if (elm == "^") {
      return 3;
    }
    return 0;
  }

  Queue< std::string > convertToPostfix(Queue< std::string > exc)
  {
    Queue< std::string > result;
    Stack< std::string > stk;
    while(!exc.isEmpty()) {
      const std::string val = exc.front();
      if (std::isdigit(static_cast< unsigned char >(val[0]))) {
        result.push(val);
      } else if (val == "(") {
        stk.push(val);
      } else if (val == ")") {
        while (!stk.isEmpty() && stk.top() != "(") {
          result.push(stk.top());
          stk.pop();
        }
        if (!stk.isEmpty()) {
          stk.pop();
        }
      } else {
        size_t valPriority = getPriority(val);
        while (!stk.isEmpty() && stk.top() != "(") {
          size_t stkPriority = getPriority(stk.top());
          if ((stkPriority > valPriority) || (stkPriority == valPriority && val != "^")) {
            result.push(stk.top());
            stk.pop();
          } else {
            break;
          }
        }
        stk.push(val);
      }
      exc.pop();
    }
    return result;
  }
}

#endif