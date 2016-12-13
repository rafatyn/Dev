#ifndef ENT_H
#define ENT_H

#include "Numeros.hpp"
#include "Real.hpp"
#include "Rad.hpp"
#include "Complex.hpp"

using namespace std;

class entero: public numero {

    private:

        int ent;

    public:

        entero(void);
        entero(int e);
        entero(const entero &e);
        ~entero(void);
        int gete(void) {return ent;}
        int gete(void) const {return ent;}
        void sete(int e) {ent = e;}
        entero& operator=(const entero y);
        entero operator+(const entero y);
        entero operator-(const entero y);
        entero operator*(const entero y);
        entero operator/(const entero y);
        const entero toEntero(void) const;
        const rad toRacional(void) const; 
        const real toReal(void) const; 
        const complex toComplejo(void) const; 
        ostream& toStream(ostream& os) const;
        istream& fromStream(istream& is);
};

#endif //ENT_H