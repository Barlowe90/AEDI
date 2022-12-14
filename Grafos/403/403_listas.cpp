#include <stdlib.h>		// Funcion exit
#include <string.h>  	// Funcion memset
#include <iostream>  	// Variables cin y cout
#include <list>
#include <queue>
//#include <sstream>

using namespace std;

#define MAX_NODOS 20000

//////////////////////////////////////////////////////////////
////////////        VARIABLES GLOBALES        ////////////////
//////////////////////////////////////////////////////////////

int nnodos;                 // Numero de nodos del grafo
list<int> G[MAX_NODOS]; 	// Lista de adyacencia
bool visitado[MAX_NODOS];   // Marcas de nodos visitados
string linea;
string num = "";
queue<int> cola;

//////////////////////////////////////////////////////////////
////////////     FUNCIONES DEL PROGRAMA       ////////////////
//////////////////////////////////////////////////////////////

void leeGrafo (void){
	cin >> nnodos;
	if (nnodos < 0 || nnodos > MAX_NODOS) {
		cerr << "Numero de nodos (" << nnodos << ") no valido\n";
		exit(0);
	}
	
	cin.ignore();

	for (int i = 0; i < MAX_NODOS; i++)
		G[i].clear();
	
	for(int i = 0; i < nnodos; i++){
		getline(cin, linea);

		for(int j = 0; j <= (int)linea.length(); j++){
			if(linea[j] == ' ' || j == (int)linea.length()){
				G[i].push_back(stoi(num));
				num = "";
			}else{
				num = num + linea[j];
			}
		}
	}
}

bool bpp(int v){
	cola.push(v);			// Pablito pinta en el suelo por donde pasa
	visitado[v]= true;
	
	list<int>::iterator EA;
	EA = G[v - 1].begin();
	//cout << "begin " << *EA << endl;
	//while(EA != G[v - 1].end() && !visitado[*EA] && *EA == nnodos ){
	while(EA != G[v - 1].end()){
		//cout << "*EA de v " << *EA << " " << v << endl;
		if(*EA == nnodos){
			cola.push(*EA);
			return true;
		}else if(!visitado[*EA]){
			if(bpp(*EA))
				return true;
				cola.push(v);
		} 
		EA++;
	}
	return false;
}

void busquedaPP (void){
	memset(visitado, 0, sizeof(visitado));		// BorrarMarcas

	while(!cola.empty())
		cola.pop();

	if(bpp(1)){
		cout << cola.size() << endl;
		while(!cola.empty()){ 
			cout << cola.front() << endl;
			cola.pop();
		}
	}else
		cout << "INFINITO" << endl;
}

void mostrarLista(void){
    list<int>::iterator EA;
    for(int i = 0; i < nnodos; i++){
        cout << i << " -> ";
        EA = G[i].begin();
        while(EA != G[i].end()){
			cout << *EA << " ";            
			EA++;
        }
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
	}
}
