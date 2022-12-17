#include <stdlib.h>		// Funcion exit
#include <string.h>  	// Funcion memset
#include <iostream>  	// Variables cin y cout
#include <list>
#include <queue>

using namespace std;

#define MAX 1000

//////////////////////////////////////////////////////////////
////////////        VARIABLES GLOBALES        ////////////////
//////////////////////////////////////////////////////////////

int ntareas;            // Numero de nodos del grafo
list<int> G[MAX]; 		// Lista de adyacencia
int tiempos[MAX];
int gradoEnt[MAX];
int acumulado[MAX];

//////////////////////////////////////////////////////////////
////////////     FUNCIONES DEL PROGRAMA       ////////////////
//////////////////////////////////////////////////////////////

void leeGrafo (void){
	cin >> ntareas;
	if (ntareas < 0 || ntareas > MAX) {
		cerr << "Numero de tareas (" << ntareas << ") no valido\n";
		exit(0);
	}
	
	cin.ignore();

	for (int i = 0; i < MAX; i++)
		G[i].clear();
		
	memset(tiempos, 0, sizeof(tiempos));
	memset(gradoEnt, 0, sizeof(gradoEnt));
	memset(acumulado, 0, sizeof(acumulado));

	string linea;
	int tiempo = 0;
	string num = "";
	
	for(int i = 0; i < ntareas; i++){		
		getline(cin, linea);

		for(int j = 0; j <= (int)linea.length(); j++){
			if(linea[j] == ' '  || linea[j] == 0){
				if(tiempo == 0){
					tiempo = stoi(num);
					tiempos[i] = tiempo;
					num = "";
					gradoEnt[i] = 0;
				}else{
					if (linea[j] != 0){
						G[stoi(num) - 1].push_back(i);
						gradoEnt[i]++;
						num = "";
					}
				}
			}else
				num = num + linea[j];
		}
		tiempo = 0;
	}
}

void ordenacionTopologica(void){
	
	queue<int> cola;
	while(!cola.empty())
		cola.pop();
	
	int contador = 1;
		
	// Metemos en una pila todos las tareas sin predecesores
	for(int v = 0; v < ntareas; v++)
		if(gradoEnt[v] == 0)
			cola.push(v);
	
	while(!cola.empty()){
		int v = cola.front();
		cola.pop();	
		contador++;
				
		//cout << "tarea " << v << endl;
		list<int>::iterator w;
		for(w = G[v].begin(); w != G[v].end(); w++){
			acumulado[*w] = max(acumulado[*w], acumulado[v] + tiempos[v]);
			gradoEnt[*w]--;
			if(gradoEnt[*w] == 0)
				cola.push(*w);	
		}
	}

	if (contador <= ntareas)
		cout << "IMPOSIBLE" << endl;
	else{		
		int mayor = 0;
		for(int i = 0; i < ntareas; i++)
			mayor = max(mayor, acumulado[i] + tiempos[i]);
		cout << mayor << endl;
	}
}

//////////////////////////////////////////////////////////////
////////////        PROGRAMA PRINCIPAL        ////////////////
//////////////////////////////////////////////////////////////

int main (void){
	int ncasos;
	cin >> ncasos;
	
	for (int i = 0; i < ncasos; i++) {
		leeGrafo();
		ordenacionTopologica();
	}
}
