#ifndef ARB_H
#define ARB_H

#include "Nodo.hpp"

using namespace std;

template<class T>
class arbol {
    
    private:
        
        nodo<T> *raiz;
        
    public:
        
        arbol(nodo<T> *raiz_=NULL):
            raiz(raiz_)
            {}
        
        void insertar(T clave)
        {
            if(raiz==NULL){
                raiz=new nodo<T>(clave,clave);
            }else{
                insertarrama(raiz, clave);
            }
        }
        
        void insertarrama(nodo<T> *nod, T clave)
        {
            if(clave < nod->clave&&nod->iz!=NULL){
                insertarrama(nod->iz, clave);
            }else if(clave > nod->clave&&nod->de!=NULL){
                insertarrama(nod->de, clave);
            }else if(clave > nod->clave&&nod->de==NULL){
                nod->de = new nodo<T>(clave,clave);
            }else if(clave < nod->clave&&nod->iz==NULL){
                nod->iz = new nodo<T>(clave,clave);
            }
        }
        
        nodo<T>* busqueda(T clave)
        {
            return buscarrama(raiz,clave);
        }
        
        nodo<T>* buscarrama(nodo<T> *nod, T clave)
        {
            if(nod==NULL){
                return NULL;
            }else if(nod->clave==clave){
                return nod;
            }else if(clave > nod->clave){
                buscarrama(nod->de, clave);
            }else if(clave < nod->clave){
                buscarrama(nod->iz, clave);
            }
        }
        
        void eliminar(T clave)
        {
            eliminarrama(raiz, clave);
        }
        
        void eliminarrama(nodo<T>* &nod, T clave)
        {
            if(nod == NULL){
            }else if(clave < nod->clave){
                eliminarrama(nod->iz, clave);
            }else if(clave > nod->clave){
                eliminarrama(nod->de, clave);
            }else{
                if(nod->de==NULL&&nod->iz==NULL){
                    nod = NULL;    
                }else if(nod->de == NULL){
                    nod = nod->iz;
                }else if(nod->iz == NULL){
                    nod = nod->de;
                }else{
                    sustituye(nod,nod->iz);   
                }
            }
        }
        
        void sustituye(nodo<T>* &el, nodo<T>* &sust)
        {
            if(sust->de!=NULL){
                sustituye(el, sust->de);
            }else{
                nodo<T> *aux=el->de;
                nodo<T> *aux2=el->iz;
                el=sust;
                nodo<T>* aux3=sust;
                sust=sust->iz;
                el->de=aux;
                if(aux2!=aux3){
                    el->iz=aux2;
                }else{
                    el->iz=sust;
                }
            }
        }
        
        void write(void)
        {
            int i=0;
            bool f=1;
            while(f){
                f=raiz->write(i);    
                cout << endl;
                i++;
            }
        }
};

#endif //ARB_H
