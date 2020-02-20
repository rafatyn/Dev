#include "equation_sys_t.hpp"

#include <iomanip>
#include <cmath>

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
            clog << "--- TRIANGULARIZACIÓN de la matriz ---"<< endl << endl;
            to_stream(clog);
            clog << endl;
            clog << "--- COMIENZO ---" << endl;
#endif        
        
for(int k=1; k<A_.get_n();k++){
            
   for (int i=k+1; i<=A_.get_m();i++){
	      double cte = A_(i,k);
	      for (int j=1; j<=A_.get_n();j++){		
		A_(i,j)=((A_(i,j)*A_(k,k))-(A_(k,j)*cte))/(A_(k,k));
	      }
	    b_(i,1)=((b_(i,1)*A_(k,k))-(b_(k,1)*cte))/(A_(k,k));
   }

#ifdef _DEPURANDO_            
            clog << "Triangulizando. Etapa "<< k << " -> "<< endl << endl;
            to_stream(clog);
            clog << endl;
#endif

}
        

#ifdef _DEPURANDO_            
            clog << "--- FIN ---" << endl << endl;
#endif          
    }
    
    void equation_sys_t::despeja(matrix_t& x) const
    {   
        x.resize_matrix(A_.get_m(),1);
        for (int i=A_.get_m();i>=1;i--){
           double cont = 0;
           for (int j= (i+1); j<=A_.get_n();j++){
             cont += ((A_(i,j))*x(j,1));
           }
        x(i,1)=((b_(i,1))-cont)/(A_(i,i));
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
