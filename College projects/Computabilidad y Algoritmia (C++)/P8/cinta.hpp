#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib> 

using namespace std;

class cinta{
    
    private:
        vector <char> cadena;
        
    public: 
        cinta(void);
        ~cinta(void);
        vector <char> get_c(void);
        bool leer_tape(char* fichero);
        void set_m(char c);
        void set_me(char c);
};