#include <cstdio>
#include "Complex.hpp"
#include "Rad.hpp"

using namespace std;

template<class T>
class calc {
    public:
        T suma(T x, T y) {return x+y;}
        T resta(T x, T y) {return x-y;}
        T mult(T x, T y) {return x*y;}
        T divi(T x, T y) {return x/y;}
};