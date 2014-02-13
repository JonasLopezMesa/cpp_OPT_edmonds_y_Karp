//
//  grafo.h
//  Práctica_Grafos
//
//  Created by Jonás López Mesa on 27/03/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Pra_ctica_Grafos_grafo_h
#define Pra_ctica_Grafos_grafo_h

#include <fstream>
#include <vector>
#include <list>
#include <iostream>
using namespace std;

const unsigned UERROR = 65000;
const int maxint = 1000000;

// Definición de un elemento de una lista de Adyacencia
typedef struct {
    unsigned    j; // nodo
    int         c; // peso, longitud, etc
    int         residuo;
    unsigned    inv;
}ElementoLista;
// Definición de una lista de adyacencia de un nodo
typedef vector<ElementoLista> LAnodo;

class GRAFO
{
    unsigned    n; //dimensión
    unsigned    m; //numero de aristas o arcos.
    vector<LAnodo> LS; // Lista de adyacencia de los Sucesores 
    void Amplitud(unsigned s, unsigned t, vector<unsigned> &pred, vector<unsigned> &pospred, vector<int> &CuelloBotella);
public:
    GRAFO(char nombrefichero[]); // constructor
    ~GRAFO(); // destructor
    void MostrarGrafo(); // Método para mostrar el grafo por pantalla 
    void Edmonds_Karp();
};


#endif
