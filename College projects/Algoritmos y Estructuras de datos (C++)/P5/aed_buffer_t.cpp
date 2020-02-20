#include "aed_buffer_t.hpp"

namespace AED{
  
  aed_buffer_t::aed_buffer_t(int max_sz):
  
     buffer_(),
     max_sz_(max_sz),
     curr_sz_(0)
     {}
     
  aed_buffer_t::~aed_buffer_t(void){
  
     flush();
  }
  
  void aed_buffer_t::flush(void){
    
    while(!buffer_.empty()){
      cout << buffer_.get();
    }
    cout << endl;
    curr_sz_ = 0;
  }
  
  void aed_buffer_t::put(char c){
    
    if(max_sz_ == curr_sz_){
      flush();
    }
    
    buffer_.put(c);
    curr_sz_++;
  }
}
     
