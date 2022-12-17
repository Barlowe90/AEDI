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
list<int> pedrecesores[MAX];

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
	
	for (int i = 0; i < MAX; i++)
		pedrecesores[i].clear();
		
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
						pedrecesores[i].push_back(stoi(num));
						gradoEnt[i]++;
						num = "";
					}
				}
			}else{
				num = num + linea[j];
			}
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
		//cout << "Estamos en gradoEnt[v] " << gradoEnt[v] << ". De la tarea " << v << endl;
		if(gradoEnt[v] == 0)
			//cout << "cola.push(v) v -> " << v << endl; 
			cola.push(v);
	
	while(!cola.empty()){
		int v = cola.front();
		//cout << "Cogemos la siguiente tarea de la cola: (v) y la sacamos " << v << endl;
		cola.pop();	
		contador++;
		//cout << "orden[v] despues contador " << orden[v] << endl;
				
		list<int>::iterator pe;
		int max = 0;
		int tiempoPedrecesor = 0;
		//cout << "tarea " << v + 1 << endl;
		for(pe = pedrecesores[v].begin(); pe != pedrecesores[v].end(); pe++){
			//cout << "*pedrecesor " << *pe << endl;
			tiempoPedrecesor = acumulado[*pe - 1];
			//cout << "tiempoPedrecesor " << acumulado[*pe - 1] << endl;
			if(tiempoPedrecesor > max)
				max = tiempoPedrecesor;
		}
		//cout << "tiempos[v] " << tiempos[v] << " - max " << max << endl;
		acumulado[v] = tiempos[v] + max;
		//cout << "acumulado[v] " << acumulado[v] << endl;
		
		list<int>::iterator w;
		for(w = G[v].begin(); w != G[v].end(); w++){
			//cout << "Iteramos con G[v] (*w) " << *w << endl;
			//cout << "Su gradoEnt[*w] es " << gradoEnt[*w] << endl;
			gradoEnt[*w]--;
			//cout << "Quitamos 1 -> G[*w]-- : " << gradoEnt[*w] << endl;
			if(gradoEnt[*w] == 0)
				cola.push(*w);	
		}
	}

	if (contador <= ntareas)
		cout << "IMPOSIBLE" << endl;
	else{		
		int mayor = 0;
		for(int i = 0; i < ntareas; i++){
			//cout << "acumulado[i] " << acumulado[i] << endl;
			if(acumulado[i] > mayor)
				mayor = acumulado[i];
		}
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
