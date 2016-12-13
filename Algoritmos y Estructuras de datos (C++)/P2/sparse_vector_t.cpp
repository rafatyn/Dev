#include "sparse_vector_t.hpp"

#include <cmath>

#include <iostream>
#include <iomanip>

using namespace std;

sparse_vector_t::sparse_vector_t(const vector_t& v, double eps):  // Este metodo se encarga de calcular los elementos no nulos a partir del vector y de la exactitud de la maquina (eps)
	
  n_(v.get_n()),
  nz_(0),
  val_(NULL),
  inx_(NULL)
  {

  for(int i=0;i<n_;i++){
    if(fabs(v.get_val(i)) > eps){
    nz_ ++;
    }
  }
	
 inx_= new int [nz_];
 val_= new double [nz_];

   int cont=0;

     for(int i=0;i<n_;i++){
   	if (fabs(v.get_val(i)) > eps){
        val_[cont]=v.get_val(i);
	inx_[cont]=i;		
	cont++;
		  
	}
     }

}

sparse_vector_t::sparse_vector_t(void):  // Este metodo es el constructor por defecto

	n_(0),
	nz_(0),
	val_(NULL),
	inx_(NULL)
	{

}

sparse_vector_t::~sparse_vector_t(void)  // Este metodo es el destructor
{
    if ((val_ != NULL)||(inx_ !=NULL)){

        delete [] val_;
        val_ = NULL;
        delete [] inx_;
        inx_ = NULL;
	nz_=n_=0;

	}
	
}

sparse_vector_t::sparse_vector_t(const sparse_vector_t &w ):

	n_(w.n_),
	nz_(w.nz_),
	val_(NULL),
	inx_(NULL)
	{
  
  for(int i=0;i<w.nz_;i++){

     val_[i]=w.val_[i];
  }

  for(int j=0;j<w.nz_;j++){

      inx_[j]=w.inx_[j];
  }
	  
}

ostream& sparse_vector_t::write(ostream& os) const  // Este metodo muestra los resultados por pantalla
{

    os << endl << "Tamaño del vector:" << setw(3) << n_ << endl;
    os << "Numero de elementos distintos de cero:" << setw(3) << nz_ << endl << endl;
    os << "Elementos del vector:   ";

    for(int i = 0; i < nz_; i++){  // Este bucle se encarga de mostrar por pantalla los elementos no nulos 

        os << setw(8) << fixed << setprecision(4) << val_[i] << " ";
    }
    
    os << endl;
    os << "Lugar de los elementos: ";
        
    for(int i = 0; i < nz_; i++)  // Este bucle se encarga de mostrar por pantalla el lugar de los valores no nulos mostardos anteriormente

        os << setw(8) << inx_[i] << " ";    
    
    os << endl;
    
    return os;
}

double sparse_vector_t::scal_prod(const vector_t& v)  // Este metodo se encarga de calcular el producto escalar 
{

 double prod_= 0.0;
 
 for (int i=0; i<nz_; i++){
   prod_ += val_[i]*v.get_val(inx_[i]);
 }
 

 return prod_;

}

double sparse_vector_t::suma_vector(const vector_t& v)  // Este metodo suma los elementos del vector
{

  double suma_= 0.0;
 
  for (int i=0; i<nz_; i++)
    suma_ += val_[i];
  

  return suma_;
}


int sparse_vector_t::minimo_vector(void)
{
  
  double minimo_= val_[0];
  int pos_ = 0;

  for (int i=0; i<=nz_; i++)
    if (minimo_>= val_[i]){
      minimo_=val_[i];
      pos_=inx_[i];
    }

 return pos_;

}
