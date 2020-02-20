#include "matriz_t.hpp"

int main (void){
int i;
    matriz_t A;
    matriz_t B(3,2);
    matriz_t C(2,3);
    B.rellena_matriz_t();
    C.rellena_matriz_t();
    cout << endl << "------------------Primera matriz:-------------------" << endl;
    B.imprime_matriz_t();
    cout << endl << "------------------Segunda matriz:-------------------" << endl;
    C.imprime_matriz_t();
    cout << endl << "Multiplicacion de la matriz primera por la matriz segunda:";
    A.producto_matrices(B,C);
    A.imprime_matriz_t();
    cout << endl << "Indique el numro de la fila que quiere sumar ";
    cin >> i;
    A.suma_fila_matriz_t(i);
    A.suma_diagonal();
    A.rellena_matriz_t_cero(); 
    cout << endl << "Multiplicacion de la matriz segunda por la matriz primera:";   
    A.producto_matrices(C,B);
    A.imprime_matriz_t();
    cout << endl << "Indique el numro de la fila que quiere sumar ";
    cin >> i;
    A.suma_fila_matriz_t(i);
    A.suma_diagonal();
    cout << endl;
}
