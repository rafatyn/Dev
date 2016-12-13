#pragma once

#include <iostream>
#include "dll_node_t.hpp"

using namespace std;


 namespace AED {

   class dll_char_node_t: public dll_node_t {
   private:
      char c_;

   public:
      dll_char_node_t(char c);
      virtual ~dll_char_node_t(void);

      virtual ostream& write(ostream& os) const;

      char get_data(void);
   };
 }
