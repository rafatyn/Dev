#ifndef REAL_H
#define REAL_H

#include "Numeros.hpp"
#include "Entero.hpp"
#include "Rad.hpp"
#include "Complex.hpp"

using namespace std;

class real: public numero {

    private:

        double re;

    public:

        real(void);
        real(double r);
        real(const real &r);
        ~real(void);
        double getr(void) {return re;}
        double getr(void) const {return re;}
        void setr(double r) {re = r;}
        real& operator=(const real y);
        real operator+(const real y);
        real operator-(const real y);
        real operator*(const real y);
        real operator/(const real y);
        const entero toEntero(void) const;
        const rad toRacional(void) const; 
        const real toReal(void) const; 
        const complex toComplejo(void) const; 
        ostream& toStream(ostream& os) const;
        istream& fromStream(istream& is);
};

#endif //REAL_H