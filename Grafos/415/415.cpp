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
int orden[MAX];

int acumulado[MAX];
bool sumado[MAX];
list<int> padres[MAX];

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
	memset(orden, 0, sizeof(orden));
	memset(acumulado, 0, sizeof(acumulado));
	memset(sumado, 0, sizeof(sumado));
	memset(padres, 0, sizeof(padres));

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
						padres[i].push_back(stoi(num));
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
		
	//cout << " ----------------------------------------------------- " << endl;
	// Metemos en una pila todos las tareas sin predecesores
	for(int v = 0; v < ntareas; v++)
		//cout << "Estamos en gradoEnt[v] " << gradoEnt[v] << ". De la tarea " << v << endl;
		if(gradoEnt[v] == 0)
			//cout << "cola.push(v) v -> " << v << endl; 
			cola.push(v);
	
	while(!cola.empty()){
		int v = cola.front();
		//cout << "Cogemos la siguiente tarea de la cola: (v) " << v << endl;
		cola.pop();
		//cout << "La sacamos" << endl;
		orden[v] = contador;
		
		contador++;
		//cout << "orden[v] despues contador " << orden[v] << endl;
		
		if(!sumado[v]){
			acumulado[v] = tiempos[v];
			sumado[v] = true;
		}
		
		//list<int>::iterator padre;
		//padre = padres[v].begin();
		
		list<int>::iterator w;
		for(w = G[v].begin(); w != G[v].end(); w++){
			//cout << " ------------- WHILEEEEEEEEEE --------------- " << endl;
			//cout << "Iteramos con G[v] (*w) " << *w << endl;
			//cout << "Su gradoEnt[*w] es " << gradoEnt[*w] << endl;
			gradoEnt[*w]--;
			//cout << "Quitamos 1 -> G[*w]-- : " << gradoEnt[*w] << endl;
			if(gradoEnt[*w] == 0){
				//cout << "Si G[*w] == 0 " <<gradoEnt[*w] << endl;
				//cout << "Lo metemos en la cola.push[*w] " << endl;
				cola.push(*w);	
				
				//cout << "*w y ntareas " << *w <<  " " << ntareas << endl;				
				acumulado[*w] = acumulado[*w] + acumulado[v];
				acumulado[*w] = acumulado[*w] + tiempos[*w];	
				//cout << "acu *w" << acumulado[*w] << endl;
				sumado[*w] = true;
			}
		}
	}

	if (contador <= ntareas)
		cout << "IMPOSIBLE" << endl;
	else{
		int mayor = 0;
		for(int i = 0; i < ntareas; i++){
			//cout << "i " << i << ". acum[i] " << acumulado[i] << endl;
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
