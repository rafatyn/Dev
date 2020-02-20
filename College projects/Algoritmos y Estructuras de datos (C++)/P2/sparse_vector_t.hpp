#pragma nce

#include "vector_t.hpp"

class sparse_vector_t{

private:
	int n_;  // Esta variable alberga la longitud del vector
	int nz_;  // Esta variable contiene la cantidad de numeros no nulos
	double* val_;  // Este puntero contiene los elementos del vector
	int* inx_;  // Este puntero contiene la posicion de los elementos del vector
public:

	sparse_vector_t(const vector_t& v, double eps);  // Este metodo se encarga de calcular los elementos no nulos a partir del vector y de la exactitud de la maquina (eps)
	sparse_vector_t(void);  // Este es el constructor por defecto
	sparse_vector_t(const sparse_vector_t &w);
	~sparse_vector_t(void); // Este es el destructor
	ostream& write(ostream& os) const;  // Este metodo se encarga de mostrar por pantalla los elementos solicitados del vector
	double scal_prod(const vector_t& v);  // Este metodo se encarga de calcular el producto escalar
        double suma_vector(const vector_t& v);  // Este metodo suma los elementos del vector
        int minimo_vector(void);  // Este metodo halla el la posicion del valor minimo del vector
};
