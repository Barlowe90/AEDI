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
int tiempos[1000];
int gradoEnt[1000];
int orden[1000];
//queue<int> cola;

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

	string linea;
	int tiempo = 0;
	string num = "";
	
	for(int i = 1; i <= ntareas; i++){		
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
						G[stoi(num)].push_back(i);
						gradoEnt[i]++;
						num = "";
					}
				}
			}else{
				num = num + linea[j];
			}
		}
		//gradoEnt[i] = G[i].size();
		tiempo = 0;
	}
}

void ordenacionTopologica(void){
	
	queue<int> cola;
	while(!cola.empty())
		cola.pop();
	
	int contador = 1;
		
	cout << " ----------------------------------------------------- " << endl;
	// Metemos en una pila todos las tareas sin predecesores
	for(int v = 1; v <= ntareas; v++){
		//cout << "Estamos en gradoEnt[v] " << gradoEnt[v] << ". De la tarea " << v << endl;
		if(gradoEnt[v] == 0){
			//cout << "cola.push(v) v -> " << v << endl; 
			cola.push(v);
		}
	}
	
	while(!cola.empty()){
		int v = cola.front();
		cout << "Cogemos la siguiente tarea de la cola: (v) " << v << endl;
		cola.pop();
		cout << "La sacamos" << endl;
		//cout << "orden[v] antes contador " << orden[v] << endl;
		orden[v] = contador;
		
		contador++;
		//cout << "orden[v] despues contador " << orden[v] << endl;
		
		
		cout << "Tiempo de v :" << tiempos[v] << endl;

		list<int>::iterator w;
		for(w = G[v].begin(); w != G[v].end(); w++){
			cout << " ------------- WHILEEEEEEEEEE --------------- " << endl;
			cout << "Iteramos con G[v] (*w) " << *w << endl;
			cout << "Su gradoEnt[*w] es " << gradoEnt[*w] << endl;
			gradoEnt[*w]--;
			cout << "Quitamos 1 -> G[*w]-- : " << gradoEnt[*w] << endl;
			if(gradoEnt[*w] == 0){
				cout << "Si G[*w] == 0 " <<gradoEnt[*w] << endl;
				cout << "Lo metemos en la cola.push[*w] " << endl;
				cola.push(*w);
			}
		}
	}
	
	cout << " ----- FIN ----- WHILEEEEEEEEEE --------------- " << endl;
	
	if (contador <= ntareas)
		cout << "IMPOSIBLE" << endl;
	else
		cout << "Posible" << endl;
}

void mostrarLista(void){
    list<int>::iterator EA;
    for(int i = 1; i <= ntareas; i++){
        cout << "Tarea " << i << " -> ";
        cout << "tiempo " << tiempos[i];
        cout << " - grado Entrada " << gradoEnt[i] << " . Adyacentes :" ;
        
        EA = G[i].begin();
        while(EA != G[i].end()){
			cout <<  *EA << " ";            
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
	
	for (int i = 0; i < ncasos; i++) {
		leeGrafo();
		//mostrarLista();
		ordenacionTopologica();
	}
}
