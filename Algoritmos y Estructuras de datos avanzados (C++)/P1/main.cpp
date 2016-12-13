#include "Vector.hpp"
#include "Sll.hpp"
#include "Pila.hpp"
#include "Cola.hpp"

int main(void){
    /*
    vector auxv(5);
    sll auxs;
    pila auxp;
    cola auxc;
    
    auxv.setdato('e',0);
    auxv.setdato('l',1);
    auxv.setdato('e',2);
    auxv.setdato('l',3);
    auxv.write(cout);
    
    nodo auxn1('p');
    auxs.insertini(&auxn1);
    nodo auxn2('e');
    auxs.insertini(&auxn2);
    nodo auxn3('p');
    auxs.insertini(&auxn3);
    nodo auxn4('e');
    auxs.insertini(&auxn4);
    auxs.write(cout);
    cout << auxs.extractini()->getval() << endl;
    
    auxp.push('f');
    auxp.push('o');
    auxp.push('f');
    auxp.push('o');
    auxp.write(cout);
    cout << auxp.pop() << " ";
    cout << auxp.pop() << " ";
    cout << auxp.pop() << " ";
    cout << auxp.pop() << " ";
    cout << auxp.pop() << endl;
    
    auxc.push('b');
    auxc.push('e');
    auxc.push('b');
    auxc.push('e');
    auxc.write(cout);
    cout << auxc.pop() << " ";
    cout << auxc.pop() << " ";
    cout << auxc.pop() << " ";
    cout << auxc.pop() << " ";
    cout << auxc.pop() << endl;
    */
    
    pila p;
    cola c;
    int x;
    
    do{
        cout << endl <<"Que desea hacer?:" << endl << "0.Salir" << endl << "1.Usar un vector" << endl << "2.Usar una pila" << endl << "3.Usar una cola" << endl << "Opcion:";
        cin >> x;
        switch(x){
            case 0:
            break;
            case 1:
            {
                int y;
                int sz;
                cout << endl << "De que tamaño sera el vector?: ";
                cin >> sz;
                vector v(sz);
                do{
                    cout << endl << "Que desea hacer?:" << endl << "0.Salir" << endl << "1.Introducir/Cambiar valor" << endl << "2.Ver el valor de una posicion" << endl << "3.Ver el contenido del vector" << endl << "Opcion: ";
                    cin >> y;
                    switch(y){
                        case 0:
                        break;
                        case 1:
                        {
                            int pos;
                            dato val;
                            cout << endl << "Posicion del valor a introducir/cambiar: ";
                            cin >> pos;
                            cout << endl << "Valor nuevo: ";
                            cin >> val;
                            v.setdato(val,pos);
                            cout << endl << "Valor cambiado" << endl;
                        }
                        break;
                        case 2:
                        {
                            int pos;
                            cout << endl << "Posicion del valor que desea conocer: ";
                            cin >> pos;
                            cout << endl << "El dato de la posicion " << pos << " es: " << v.getdato(pos) << endl;
                        }
                        break;
                        case 3:
                            cout << endl << "El contenido del vector es: ";
                            v.write(cout);
                            cout << endl;
                        break;
                        default:
                            cout << endl << "Opcion no valida" << endl;
                    }
                }while(y!=0);  
            }
            break;
            case 2:
            {
                int y;
                do{
                    cout << endl << "Que desea hacer?:" << endl << "0.Salir" << endl << "1.Introducir valor en la pila" << endl << "2.Sacar valor de la pila" << endl << "3.Ver el contenido de la pila" << endl << "Opcion: ";
                    cin >> y;
                    switch(y){
                        case 0:
                        break;
                        case 1:
                            dato val;
                            cout << endl << "Valor a introducir: ";
                            cin >> val;
                            p.push(val);
                            cout << endl << "Valor introducido" << endl;                            
                        break;
                        case 2:
                            cout << endl << "El dato es: " << p.pop() << endl;
                        break;
                        case 3:
                            cout << endl << "El contenido de la pila es: ";
                            p.write(cout);
                            cout << endl;
                        break;
                        default:
                            cout << endl << "Opcion no valida" << endl;
                    }
                }while(y!=0);
            }
            break;
            case 3:
            {
                int y;
                do{
                    cout << endl << "Que desea hacer?:" << endl << "0.Salir" << endl << "1.Introducir valor en la cola" << endl << "2.Sacar valor de la cola" << endl << "3.Ver el contenido de la cola" << endl << "Opcion: ";
                    cin >> y;
                    switch(y){
                        case 0:
                        break;
                        case 1:
                            dato val;
                            cout << endl << "Valor a introducir: ";
                            cin >> val;
                            c.push(val);
                            cout << endl << "Valor introducido" << endl;                            
                        break;
                        case 2:
                            cout << endl << "El dato es: " << c.pop() << endl;
                        break;
                        case 3:
                            cout << endl << "El contenido de la cola es: ";
                            c.write(cout);
                            cout << endl;
                        break;
                        default:
                            cout << endl << "Opcion no valida" << endl;
                    }
                }while(y!=0);
            }
            break;
            default:
                cout << endl << "Opcion no valida" << endl;
        }
    }while(x!=0);     
    
}
    