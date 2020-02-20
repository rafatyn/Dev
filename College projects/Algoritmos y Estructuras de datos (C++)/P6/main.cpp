#include "equation_sys_t.hpp"


int main (void)
{
  
  
    AED::matrix_t u; 
    AED::equation_sys_t equation_system;
     
  
    cin >>equation_system;
    cin >> u;

    AED::matrix_t x;
    AED::matrix_t y;
    
    equation_system.resuelve(x);
    equation_system.solve(y);
    
    cout << "--- SOLUCIÓN ---" << endl << "Metodo primero:" << endl;  
    cout << x << endl;
    cout << "Metodo segundo:" << endl;
    cout << y << endl;
    
    
    u.Obtener_menor(x,3,3);
    cout << "Matriz menor:" << endl << x << endl; 
    
    cout << "Determinante de la matriz:  " << u.determinante() << endl;
    
 
}
