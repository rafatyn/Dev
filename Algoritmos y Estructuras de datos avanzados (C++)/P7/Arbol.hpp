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
            
        ~arbol(void){
            delete raiz;
        }
        
        void insertar(T clave)
        {
            nodo<T> *nuevo = new nodo<T>(clave,clave,0);
            bool crece=0;
            insertarrama(raiz, nuevo, crece);
        }
        
        void insertarrama(nodo<T>* &nod, nodo<T>* nuevo, bool &crece)
        {
            if(nod==NULL){
                nod = nuevo;
                crece = true;
            }else if(nuevo->clave > nod->clave){
                insertarrama(nod->de, nuevo, crece);
                if(crece) insertar_balancea_de(nod, crece);
            }else if(nuevo->clave < nod->clave){
                insertarrama(nod->iz, nuevo, crece);
                if(crece) insertar_balancea_iz(nod, crece);
            }
        }
        
        void insertar_balancea_iz(nodo<T>* &nod, bool &crece)
        {
            switch(nod->bal){
                case -1:
                    nod->bal = 0;
                    crece = false;
                break;
                case 0:
                    nod->bal = 1;
                break;
                case 1:
                    nodo<T> *aux = nod->iz;
                    if(aux->bal==1){
                        rotacion_II(nod);    
                    }else{
                        rotacion_ID(nod);
                    }
                    crece = false;
                break;
            }
        }
        
        void insertar_balancea_de(nodo<T>* &nod, bool &crece)
        {
            switch(nod->bal){
                case 1:
                    nod->bal = 0;
                    crece = false;
                break;
                case 0:
                    nod->bal = -1;
                break;
                case -1:
                    nodo<T> *aux = nod->de;
                    if(aux->bal==-1){
                        rotacion_DD(nod);    
                    }else{
                        rotacion_DI(nod);
                    }
                    crece = false;
                break;
            }
        }
        
        void rotacion_II(nodo<T>* &nod)
        {
            nodo<T> *aux = nod->iz;
            nod->iz = aux->de;
            aux->de = nod;
            if(aux->bal==1){
                nod->bal=0;
                aux->bal=0;
            }else{
                nod->bal=1;
                aux->bal=-1;
            }
            nod=aux;
        }
        
        void rotacion_DD(nodo<T>* &nod)
        {
            nodo<T> *aux = nod->de;
            nod->de = aux->iz;
            aux->iz = nod;
            if(aux->bal==-1){
                nod->bal=0;
                aux->bal=0;
            }else{
                nod->bal=-1;
                aux->bal=1;
            }
            nod=aux;
        }
        
        void rotacion_ID(nodo<T>* &nod)
        {
            nodo<T>* aux1 = nod->iz;
            nodo<T>* aux2 = aux1->de;
            nod->iz = aux2->de;
            aux2->de = nod;
            aux1->de = aux2->iz;
            aux2->iz = aux1;
            if(aux2->bal == -1) aux1->bal = 1;
            else aux1->bal = 0;
            if (aux2->bal == 1) nod->bal = -1;
            else nod->bal = 0;
            aux2->bal = 0;
            nod = aux2;
        }
        
        void rotacion_DI(nodo<T>* &nod)
        {
            nodo<T>* aux1 = nod->de;
            nodo<T>* aux2 = aux1->iz;
            nod->de = aux2->iz;
            aux2->iz = nod;
            aux1->iz = aux2->de;
            aux2->de = aux1;
            if (aux2->bal==1) aux1->bal=-1;
            else aux1->bal=0;
            if (aux2->bal==-1) nod->bal=1;
            else nod->bal = 0;
            aux2->bal = 0;
            nod = aux2;
        }
        
        nodo<T>* busqueda(T clave)
        {
            return buscarrama(raiz,clave);
        }
        
        nodo<T>* buscarrama(nodo<T> *nod, T clave)
        {
            if(nod==NULL){
                return NULL;
            }else if(clave > nod->clave){
                buscarrama(nod->de, clave);
            }else if(clave < nod->clave){
                buscarrama(nod->iz, clave);
            }else if(nod->clave==clave){
                return nod;
            }
        }
        
        void eliminar(T clave)
        {
            bool decrece=false;
            eliminarrama(raiz, clave, decrece);
        }
        
        void eliminarrama(nodo<T>* &nod, T clave, bool &decrece)
        {
            if(nod == NULL){
                return;
            }else if(clave < nod->clave){
                eliminarrama(nod->iz, clave, decrece);
                if(decrece) eliminar_balancea_iz(nod,decrece);
            }else if(clave > nod->clave){
                eliminarrama(nod->de, clave, decrece);
                if(decrece) eliminar_balancea_de(nod, decrece);
            }else{
                if(nod->de == NULL){
                    nod = nod->iz;
                    decrece=true;
                }else if(nod->iz == NULL){
                    nod = nod->de;
                    decrece=true;
                }else{
                    sustituye(nod,nod->iz,decrece);
                    if(decrece) eliminar_balancea_iz(nod,decrece);
                }
            }
        }
        
        void sustituye(nodo<T>* &el, nodo<T>* &sust, bool &decrece)
        {
            if(sust->de!=NULL){
                sustituye(el, sust->de, decrece);
                if(decrece) eliminar_balancea_de(sust, decrece);
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
                if(el->bal==0){
                    el->bal = -1;
                }else{
                    el->bal = 0;
                }
                decrece=true;
            }
        }
        
        void eliminar_balancea_iz(nodo<T>* &nod, bool &decrece)
        {
            switch(nod->bal){
                case 1:
                    nod->bal = 0;
                break;
                case 0:
                    nod->bal = -1;
                    decrece=false;
                break;
                case -1:
                    nodo<T> *aux = nod->de;
                    if(aux->bal > 0){
                        rotacion_DI(nod);    
                    }else{
                        if(aux->bal == 0) decrece=false;
                        rotacion_DD(nod);
                    }
                break;
            }
        }
        
        void eliminar_balancea_de(nodo<T>* &nod, bool &decrece)
        {
            switch(nod->bal){
                case -1:
                    nod->bal = 0;
                break;
                case 0:
                    nod->bal = 1;
                    decrece=false;
                break;
                case 1:
                    nodo<T> *aux = nod->iz;
                    if(aux->bal < 0){
                        rotacion_ID(nod);    
                    }else{
                        if(aux->bal == 0) decrece=false;
                        rotacion_II(nod);
                    }
                break;
            }
        }
        
        void write(void)
        {
            int i=0;
            bool f=1;
            if(raiz!=NULL){
                while(f){
                    f=raiz->write(i);    
                    cout << endl;
                    i++;
                }
            }else{
                cout << "[.]" << endl;    
            }
        }
};

#endif //ARB_H
