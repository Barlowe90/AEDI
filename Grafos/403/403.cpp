#include <stdlib.h>  // Funcion exit
#include <string.h>  // Funcion memset
#include <iostream>  // Variables cin y cout
#include <list>
using namespace std;

#define MAX_NODOS 5

//////////////////////////////////////////////////////////////
////////////        VARIABLES GLOBALES        ////////////////
//////////////////////////////////////////////////////////////

int nnodos;                   // Numero de nodos del grafo
bool G[MAX_NODOS][MAX_NODOS]; // Matriz de adyacencia
bool visitado[MAX_NODOS];     // Marcas de nodos visitados
string num1, num2;
string linea;
list<int> lista_todos, lista_final;
list<int>::iterator EA_LT, EA_LF;
//int sitios;

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

void leeGrafo (void){
	cin >> nnodos;
	if (nnodos < 0 || nnodos > MAX_NODOS) {
		cerr << "Numero de nodos (" << nnodos << ") no valido\n";
		exit(0);
	}
	
	for(int i = 1; i <= MAX_NODOS; i++)
		for(int j = 1; j <= MAX_NODOS; j++)
			G[i][j] = 0;
		
	//cout << "Nodos " << nnodos << endl;
	cin.ignore();
	
	for (int i = 1; i <= nnodos; i++) {
		getline(cin, linea);
		funcionSeparadora(linea, num1, num2);
		int c1 = stoi(num1);
		G[i][c1]= true;
		int c2 = stoi(num2);
		if(c2 != 0)
			G[i][c2]= true;
	}
}

void bpp(int v){
	visitado[v]= true;
	//cout << "Fila" << v << endl;
	for (int w = 1; w <= nnodos; w++){
		//cout << "Columna " << w << ". De la fila " << v << endl;
		if(lista_todos.back() != v) {
			lista_todos.push_back(v);
			//cout << " - añadimos a lista el " << v << endl;
		}
		if (!visitado[w] && G[v][w]){
			bpp(w);
		}
	}
}

void busquedaPP (void){
	memset(visitado, 0, sizeof(visitado));
	lista_todos.clear();
	lista_final.clear();

	for (int v = 1; v <= nnodos; v++)
		if (!visitado[v])
			bpp(v);
}

void puedeSalir(void){	
	//sitios = 0;
	EA_LT = lista_todos.begin();

	while(EA_LT != lista_todos.end() && *EA_LT != nnodos){
		//sitios++;
		//cout << " *EA_LT " << *EA_LT;
		lista_final.push_back(*EA_LT);
		EA_LT++;
	}
	if (EA_LT != lista_todos.end()){ 
		lista_final.push_back(*EA_LT);
		//cout << " *EA_LT " << *EA_LT;
	}
	
	cout << "Sitios " << lista_final.size() << endl;
	
	EA_LF = lista_final.begin();
	while(EA_LF != lista_final.end()){
		//cout << " *EA_LF " << *EA_LF;
		EA_LF++;
	}
	cout << endl;
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
		puedeSalir();
		//if(!puedeSalir())
			//cout << "INFINITO" << endl;
	}
}
