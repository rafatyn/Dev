#include <iostream>
#include <iomanip>

using namespace std;

#include "vector_t.hpp"
#include "sparse_vector_t.hpp"

int main(void)
{
    vector_t v(6);

    v[0] = 0.0;
    v[1] = 0.0;
    v[2] = 5.0;
    v[3] = 6.0;
    v[4] = 0.0;
    v[5] = 4.0;
    

    sparse_vector_t s_v(v, 0.01);

    sparse_vector_t s_w(v, 0.001);

    sparse_vector_t s_x(v, 0.0001);

    cout << endl;

    v.write(cout);
    
    cout << endl;
    
    s_v.write(cout);
    // s_w.write(cout);
    // s_x.write(cout);
    
    cout << endl << "El resultado del producto escalar del primer vector es: " << setprecision(2) << s_v.scal_prod(v) << endl;

    cout << "La suma de los elementos del vector: " << setprecision(2) << s_v.suma_vector(v) << endl;

    cout << "El lugar del elemento mas pequeño es: " << s_v.minimo_vector() << endl;

    vector_t x(6);

    x[0] = 8.0;
    x[1] = 1.0;
    x[2] = 3.0;
    x[3] = 5.0;
    x[4] = 4.0;
    x[5] = 3.0;

    cout << "El resultado del producto escalar del segundo vector es: " << setprecision(2) << s_v.scal_prod(x) << endl << endl;


}
