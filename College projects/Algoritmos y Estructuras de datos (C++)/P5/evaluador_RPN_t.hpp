#pragma once

#include "stack_float_t.hpp"
#include <cstring>
#include <cstdlib> 

using namespace std;

namespace AED {

  class evaluador_RPN_t {
    private:
      stack_float_t stack_;

    public:
      evaluador_RPN_t(void);
      virtual ~evaluador_RPN_t(void);
      float eval(char cadena []);
  };
}
