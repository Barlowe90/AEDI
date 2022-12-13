#include <stdlib.h>  // Funcion exit
#include <string.h>  // Funcion memset
#include <iostream>  // Variables cin y cout
#include <vector>

using namespace std;

#define MAX_NODOS 10

//////////////////////////////////////////////////////////////
////////////        VARIABLES GLOBALES        ////////////////
//////////////////////////////////////////////////////////////

int nnodos;                 // Numero de nodos del grafo
vector<int> G[MAX_NODOS]; 	// Lista de adyacencia
bool visitado[MAX_NODOS];   // Marcas de nodos visitados
string num1, num2;
string linea;

//////////////////////////////////////////////////////////////
////////////     FUNCIONES DEL PROGRAMA       ////////////////
//////////////////////////////////////////////////////////////

void funcionSeparadora(string linea, string &num1, string &num2){
	if (linea.length() == 1){
		num1 = linea[0];
		num2 = "0";
	}else if (linea.length() == 3){
		num1 = linea[0];
		num2 = linea[2];
	}
}

void addNodo(vector<int> G[], int i, int num){
	G[i].push_back(num);
}

void leeGrafo (void){
	cin >> nnodos;
	if (nnodos < 0 || nnodos > MAX_NODOS) {
		cerr << "Numero de nodos (" << nnodos << ") no valido\n";
		exit(0);
	}
	
	for(int i = 1; i <= MAX_NODOS; i++)
		memset(G, 0, sizeof(G));
		
	cout << "Nodos " << nnodos << endl;
	cin.ignore();
	
	for (int i = 1; i <= nnodos; i++) {
		getline(cin, linea);
		funcionSeparadora(linea, num1, num2);
		int c1 = stoi(num1);
		int c2 = stoi(num2);
		if (c2 == 0){
			addNodo(G, i, c1);
		}
		if (c2 != 0 && c2 < c1){
			addNodo(G, i, c2);
			addNodo(G, i, c1);
		}else if (c2 != 0 && c2 > c1){
			addNodo(G, i, c1);
			addNodo(G, i, c2);
		}
	}
}

void bpp(int v){
	visitado[v]= true;
	cout << "Estamos en v: " << v << ". " << endl;
	
	for (int w : G[v]){
		cout << "Recorremos de v: " << v << ". " << endl;
		cout << "Adyacente w: " << w << endl;
		if (!visitado[w]){
			cout << "Adyacente no visitado " << w << endl;
			bpp(w);
		}
		cout << "termina for de w " << w << endl;
    }
    cout << "Fin bpp v: " << v << endl;
}

void busquedaPP (void){
	memset(visitado, 0, sizeof(visitado));		// BorrarMarcas

	for (int v = 1; v <= nnodos; v++){
		cout << "AH" << endl;
		if (!visitado[v])
			bpp(v);
	}
	cout << endl;
}

void mostrarLista(){
    for (int i = 1; i <= MAX_NODOS; i++) {
        cout << i << " -> ";
        for (int x : G[i])
            cout << x << " ";
        cout << endl;
    } 
}

//////////////////////////////////////////////////////////////
////////////        PROGRAMA PRINCIPAL        ////////////////
//////////////////////////////////////////////////////////////

int main (void){
	int ncasos;
	cin >> ncasos;
	for (int i = 1; i <= ncasos; i++) {
		cout << "Caso " << i << endl;
		leeGrafo();
		busquedaPP();
		//mostrarLista();
	}
}
