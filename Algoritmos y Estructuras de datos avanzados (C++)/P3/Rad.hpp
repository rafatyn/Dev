#ifndef RAD_H
#define RAD_H

#include "Numeros.hpp"
#include "Real.hpp"
#include "Entero.hpp"
#include "Complex.hpp"

using namespace std;


class rad: public numero {

    private:

        int num;
        int dem;

    public:

        rad(void);
        rad(int n, int d);
        rad(const rad &d);
        ~rad(void);
        int getn(void) {return num;}
        int getd(void) {return dem;}
        int getn(void) const {return num;}
        int getd(void) const {return dem;}
        void setn(int n) {num = n;}
        void setd(int d) {dem = d;}
        rad& operator=(const rad y);
        rad operator+(const rad y);
        rad operator-(const rad y);
        rad operator*(const rad y);
        rad operator/(const rad y);
        const entero toEntero(void) const;
        const rad toRacional(void) const; 
        const real toReal(void) const; 
        const complex toComplejo(void) const; 
        ostream& toStream(ostream& os) const;
        istream& fromStream(istream& is);
};

#endif //RAD_H