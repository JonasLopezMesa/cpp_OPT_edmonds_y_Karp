//
//  main.cpp
//  Práctica_Grafos
//
//  Created by Jonás López Mesa on 27/03/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "grafo.h"
int menu();
int menu ()
{
	int opc = 0;
    cout << "******************************************************" << endl;
    cout << "************************MENÚ**************************" << endl;
	cout << "*1. Cargar, Mostrar Grafo y ejecutar PRIM.           *" << endl;
    cout << "*2. Salir.                                           *" << endl;
    cout << "******************************************************" << endl;
    cout << "*Opcion:      ";
	do
	{
		cin >> opc;
		
	}while ( opc > 3 || opc < 1);
	
	return (opc);
}

int main ()
{
    char nombrefichero[50];
    int opcion;
    int x = 1;
    while(x == 1) 
    {
		opcion = menu ();
        
        if (opcion == 1) {
            cout << "Introduzca el nombre del fichero a cargar: ";
            cin >> nombrefichero;
            cout << "CONSTRUYENDO GRAFO..." << endl;
            GRAFO A(nombrefichero);
            cout << "Grafo construido" << endl;
            A.MostrarGrafo();
            A.Edmonds_Karp();
        }
		if (opcion == 2) {
            cout << "Fin del Programa" << endl;
            x=2;
            return 0;
        }
        if (opcion != 1 && opcion != 2) {
            cout << "Opción incorrecta, por favor escoja una opción correcta" << endl;
        }
    }
    return 0;
}

