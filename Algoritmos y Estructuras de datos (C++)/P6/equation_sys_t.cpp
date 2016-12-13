
#include "equation_sys_t.hpp"


namespace AED {

    equation_sys_t::equation_sys_t(void):
    A_(),
    b_()
    {}
    
    equation_sys_t::~equation_sys_t(void)
    {}
    
    void equation_sys_t::solve(matrix_t& x)
    {
        triangulariza();
        despeja(x);
    }
    
    void equation_sys_t::resuelve(matrix_t& aux)
    {
      matrix_t aux2;
      A_.inversa(aux2);
      aux.multiplica(aux2,b_);
    }
      
      
      
    
    bool equation_sys_t::verifica(const matrix_t& x, double eps) const
    {
        matrix_t Ax;
        
        Ax.multiplica(A_, x);
        
        bool iguales = true;
        for(int i = 1; (i <= Ax.get_m()) && iguales; i++){
            
            if (fabs(Ax(i, 1)- b_(i, 1)) > eps)
                iguales = false;
        }
        
        return iguales;
    }
    
    ostream& equation_sys_t::to_stream(ostream& os) const
    {
        for(int i = 1; i <= A_.get_m(); i ++){
            for(int j = 1; j <= A_.get_n(); j++)
                os << setw(10) << fixed << setprecision(4) << A_(i,j)<< " "; 
            os << " | " << setw(10) << fixed << setprecision(4) << b_(i,1)<< endl; 
        }
        return os;    
    }
    
    istream& equation_sys_t::from_stream(istream& is)
    {
        is >> A_ >> b_;
        
        return is;
    }
    
    void equation_sys_t::triangulariza(void)
    {
#ifdef _DEPURANDO_   
            clog << endl;
            clog << "--- TRIANGULARIZACIÓN de la matriz ---"<< endl;
            to_stream(clog);
            clog << endl;
            clog << "--- COMIENZO ---" << endl;
#endif        
        for(int k=1; k<=A_.get_n(); k++){
            #ifdef _DEPURANDO_            
            clog << "Triangulizando. Etapa "<< k << " -> "<< endl;
            to_stream(clog);
            clog << endl;
            #endif
            double aux = A_(k,k);
            for(int j=1; j<=A_.get_n(); j++){
                
                A_(k,j)/=aux;
            }
                b_(k,1)/= aux;

           for(int j=k+1; j<=A_.get_m(); j++){
               double d= -A_(j,k);
               for(int w=k; w<=A_.get_n();w++){
            
                A_(j,w)+=A_(k,w)*d;
                
               }
               b_(j,1)+=b_(k,1)*d;
           }
            
        }
       
#ifdef _DEPURANDO_            
            clog << "--- FIN ---" << endl;
#endif
 }


  
    void equation_sys_t::despeja(matrix_t& x) const
    {   x.resize_matrix(A_.get_m(),1);
	    
	    
	    for(int i=A_.get_m(); i>=1; i--){
	        
	        double aux=0;
	        for(int j=i+1; j<=A_.get_n();j++){
	            
	            aux+=A_(i,j)*x(j,1);
	            
	            
	        }   
	        x(i,1)=(b_(i,1)-aux)/A_(i,i);
	       
	        }
	    }
	
	
	
	
    
}


ostream&  operator<<(ostream& os, const AED::equation_sys_t& M) 
{
    return M.to_stream(os);
}

istream&  operator>>(istream& is, AED::equation_sys_t& M)
{
    return M.from_stream(is);
}

