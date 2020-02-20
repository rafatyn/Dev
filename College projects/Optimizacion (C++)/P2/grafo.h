/*
 *  GRAFO.h - definicion de la clase GRAFO
 *
 *  Autor : Antonio Sedeno Noda, Sergio Alonso
 *  Curso 2012-2013
 */

#ifndef _GRAPH_H
#define _GRAPH_H


#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

const unsigned UERROR = 65000;
const int maxint = 1000000;

// definicion de un elemento de la lista de adyacencia

typedef struct
{
	unsigned j; // nodo
	int      c; // atributo para expresar el peso, la longitud, el coste, la inversin, etc...
} ElementoLista;

// definicion del tipo de una lista de adyacencia de un nodo

typedef vector<ElementoLista> LA_nodo;


class GRAFO
 {
	// unsigned            dirigido;  //0 si el grafo es no dirigido y 1 si es dirigido
	unsigned            n;         // numero de NODOS //
	unsigned            m;         // numero de ARCOS //
	unsigned   			dirigido;  //0 si el grafo es no dirigido y 1 si es dirigido
	vector<LA_nodo>     LS;        // Lista de adyacencia de los sucesores: es una matriz donde cada fila posiblemente es posiblemente de distinto tamaño//
	vector<LA_nodo>     LP;        // Lista de adyacencia de los predecesores: es una matriz donde cada fila posiblemente es posiblemente de distinto tamaño//
 public:
     GRAFO(char nombrefichero[], int &errorapertura);
     void actualizar (char nombrefichero[], int &errorapertura);
     unsigned Es_dirigido();  //devuelve 0 si el grafo es no dirigido y 1 si es dirigido
     void Info_Grafo();
     void Mostrar_Listas(int l);
     void ListaPredecesores();
     ~GRAFO();
};


#endif
