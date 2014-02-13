//
//  grafo.cpp
//  Práctica_Grafos
//
//  Created by Jonás López Mesa on 27/03/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "grafo.h"


//////////////////////////////////////////////CONSTRUCTOR
GRAFO::GRAFO(char nombrefichero[]){ 
    unsigned int i, j, k, p;              //variables de recorrido yde almacenaje de información
	ElementoLista dummy, dummy2;                    //variable tipo ElementoLista que va a almacenar las variables j y c
	ifstream tex;                           //variable tipo ifstream que es la que irá recogiendo los datos del fichero
    cout << nombrefichero << endl;
	tex.open(nombrefichero);                //Se abre el fichero en la variable text
	if (tex.is_open())                      //Si el fichero se abrió correctamente entonces:
	{
		LS.clear();                         //vacía la lista de adyacencia de los predecesores
		tex >> n >> m;                      //
        //cout << m;
                                            //es dirigido o no
		LS.resize(n);                       //Redimensiona el vector LS(lista de sucesores) para que tenga tamaño n(números de nodos)
		for (k=0;k<m;k++)                   //por cada una de las aristas hacer:
		{
			tex >> i >> j >> p;             //recoge el nodo y a donde se dirije su arista
            dummy.j=j-1;                    
            dummy2.j=i-1;
			dummy.c=p;                      //asigna el valor del coste a dummy.c
            dummy2.c=0;
            dummy.residuo=p;
            dummy2.residuo=0;
            dummy.inv=LS[j].size();
            dummy2.inv=LS[i].size();
            
			LS[i - 1].push_back(dummy);     // introduce el la lista de adyacencia el valor de dummy, tanto la c como la j.
            LS[j - 1].push_back(dummy2);
		}
	}
	tex.close();                            //cierra el archivo
}

/////////////////////////////////////////////DESTRUCTOR
GRAFO::~GRAFO(){ 
    LS.clear(); //vacía la lista de adyacencia de los sucesores
}

void GRAFO::MostrarGrafo(){
    cout << "Atriburos del Grafo" << endl; 
    cout << n << " " << m << " " << endl;
    cout << "Lista de Sucesores" << endl;
    for (int k=0; k < LS.size(); k++) {
        for (int w=0; w < LS[k].size(); w++) {
            cout << k+1 << "--->" << LS[k][w].j+1 << " [ " << LS[k][w].c << " ]" << endl;
        }
    }

}

void GRAFO::Edmonds_Karp(){
    int maxflow = 0;
    bool camino = true;
    unsigned s,t,k;
    vector<int> CuelloBotella;
    vector<unsigned> pred, pospred;
    cout << "Introduzca el nodo fuente" << endl;
    cin >> s;
    s--;
    cout << "Introduzca el nodo sumidero" << endl;
    cin >> t;
    t--;
    while (camino == true) {
        //cout << 1 << endl;
        pred.resize(n,UERROR);
        //cout << 2 << endl;
        pospred.resize(n);
        //cout << 3 << endl;
        CuelloBotella.resize(n,maxint);
        //cout << 4 << endl;
        pred[s] = s;
        //cout << 5 << endl;
        Amplitud(s,t,pred,pospred,CuelloBotella);
        //cout << 6 << endl;
        if (pred[t] == UERROR) {
            //cout << 7 << endl;
            camino = false;
            //cout << 8 << endl;
            cout << "    El Flujo Máximo es maxflow = "  << maxflow << endl;
            //cout << 9 << endl;
            cout << " El conjunto S del [S,T]-corte está formado por todos los nodos k tales que pred[k]<>UERROR t T = V-S" << endl;
            //cout << 10 << endl;
        } else {
            //cout << 11 << endl;
            maxflow += CuelloBotella[t];
            //cout << 12 << endl;
            k = t;
            //cout << 13 << endl;
            cout << "Camino incremental:" << endl;
            //cout << 14 << endl;
            while (k != s) {
                //cout << 15 << endl;
                LS[pred[k]][pospred[k]].residuo -= CuelloBotella[t];
                //LS[pospred[k]][pred[k]].residuo += CuelloBotella[t];
                LS[k][LS[pred[k]][pospred[k]].inv].residuo += CuelloBotella[t];
                k = pred[k]; //¿?¿?¿?¿?¿?¿¿?¿¿?¿?¿?
            }
        }
    }
    cout << "Patrón de Flujo máximo es: " << endl;
    for (int i = 0; i < LS.size(); i++) {
        for (int j = 0; j < LS[i].size(); j++) {
            if (LS[i][j].c > 0) {
                cout << "El flujo máximo del nodo " << i+1  << " al nodo "<< LS[i][j].j+1 << " es " << (LS[i][j].c - LS[i][j].residuo) << endl;
                cout << "RESIDUO  de " << i+1 << " es " << LS[i][j].residuo << endl;
            }
        }
    }
}




void GRAFO::Amplitud(unsigned s, unsigned t, vector<unsigned> &pred, vector<unsigned> &pospred, vector<int> &CuelloBotella){
    cout << "AJHDLDJHLGDAH" <<LS[0][0].residuo << endl;
    list<unsigned> cola;
    cola.resize(n);
    cola.push_back(s);
    while (cola.empty() == false) {
        cout << "cola no vacía" << endl;
        cout << "el primer elemento de la cola es: " << cola.front() << endl;
        unsigned i = cola.front();
        cola.pop_front();
        for (int k = 0; k < LS[i].size() ; k++) {
            if ((pred[LS[i][k].j] == UERROR) && (LS[i][k].residuo > 0)) {
                cout << "-------------------------" << endl;
                cout << "El residuo de " << "LS["<<i<<"]["<<k<<"]" " es: " << LS[i][k].residuo << endl;
                pred[LS[i][k].j] = i;
                pospred[LS[i][k].j] = k; //PUEDE QUE ESTÉ MAL
                if (CuelloBotella[i] < LS[i][k].residuo) {
                    CuelloBotella[LS[i][k].j] = CuelloBotella[i];
                    cout << "El residuo es mayor que el cuello de botella" << endl;
                } else {
                    CuelloBotella[LS[i][k].j] = LS[i][k].residuo;
                    cout << "El residuo es menor o igual que el cuello de botella" << endl;
                }
                cola.push_back(LS[i][k].j); 
                //cout << LS[i][k].j << endl;
                //cout << "pred[LS[i][j].j] " << pred[LS[i][j].j] << " pospred[LS[i][j].j] " << pospred[LS[i][j].j]  << " CuelloBotella[LS[i][j].j] " << CuelloBotella[LS[i][j].j] << endl;
                cout << "Se saca de la cola el elemento: " << LS[i][k].j << endl;
            } 
        }
    }
}














