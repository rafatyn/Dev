#pragma once

#include "queue_char_t.hpp"

namespace AED{
  
  class aed_buffer_t {
    
    private:
      queue_char_t buffer_;
      int max_sz_;
      int curr_sz_;
      
    public:
      aed_buffer_t(int max_sz);
      ~aed_buffer_t(void);
      void flush(void);
      void put(char c);
  };
}
