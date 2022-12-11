#include <stdlib.h>  // Funcion exit
#include <string.h>  // Funcion memset
#include <iostream>  // Variables cin y cout
#include <queue>
#include <list>
using namespace std;

#define MAX_NODOS 26

//////////////////////////////////////////////////////////////
////////////        VARIABLES GLOBALES        ////////////////
//////////////////////////////////////////////////////////////

int nnodos;                   // Numero de nodos del grafo
int naristas;                 // Numero de aristas del grafo
bool G[MAX_NODOS][MAX_NODOS]; // Matriz de adyacencia
bool visitado[MAX_NODOS];     // Marcas de nodos visitados
queue<int> cola;
int frente;
list<int> w;

//////////////////////////////////////////////////////////////
////////////     FUNCIONES DEL PROGRAMA       ////////////////
//////////////////////////////////////////////////////////////

void leeGrafo (void){
	cin >> nnodos >> naristas;
	if (nnodos<0 || nnodos>MAX_NODOS) {
		cerr << "Numero de nodos (" << nnodos << ") no valido\n";
		exit(0);
	}
	memset(G, 0, sizeof(G));
	char c1, c2;
	for (int i = 0; i < naristas; i++) {
		cin >> c1 >> c2;
		G[c1-'A'][c2-'A']= true;
	}
}

void bpa(int v){
	visitado[v]= true;
	cola = {};
	cola.push(v);
	// cout << char(v+'A');
	while(!cola.empty()){
		frente = cola.front();
		cout << char(frente+'A');
		cola.pop();
		for (int w = 0; w < frente; w++){
			if (!visitado[w]){
				visitado[w] = true;
				cola.push(w);
			}
		}
	}
}

void busquedaPA (void){
	memset(visitado, 0, sizeof(visitado));
	for (int v= 0; v<nnodos; v++)
		if (!visitado[v])
			bpa(v);
	cout << endl;
}

//////////////////////////////////////////////////////////////
////////////        PROGRAMA PRINCIPAL        ////////////////
//////////////////////////////////////////////////////////////

int main (void){
	int ncasos;
	cin >> ncasos;
	for (int i= 0; i<ncasos; i++) {
		leeGrafo();
		busquedaPA();
	}
}
