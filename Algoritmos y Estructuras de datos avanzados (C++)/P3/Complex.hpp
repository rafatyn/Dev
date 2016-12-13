#ifndef COMPLEX_H
#define COMPLEX_H

#include "Numeros.hpp"
#include "Real.hpp"
#include "Entero.hpp"
#include "Rad.hpp"

using namespace std;


class complex: public numero {

    private:

        int rel;
        int imaginario;

    public:

        complex(void);
        complex(int r, int i);
        complex(const complex &c);
        ~complex(void);
        int getr(void) {return rel;}
        int geti(void) {return imaginario;}
        int getr(void) const {return rel;}
        int geti(void) const {return imaginario;}
        void setr(int r) {rel = r;}
        void seti(int i) {imaginario = i;}
        complex& operator=(const complex y);
        complex operator+(const complex y);
        complex operator-(const complex y);
        complex operator*(const complex y);
        complex operator/(const complex y);
        const entero toEntero(void) const;
        const rad toRacional(void) const; 
        const real toReal(void) const; 
        const complex toComplejo(void) const; 
        ostream& toStream(ostream& os) const;
        istream& fromStream(istream& is);
};

#endif //COMPLEX_H