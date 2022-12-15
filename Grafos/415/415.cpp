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
			if(linea[j] == ' ' || j == (int)linea.length()){
				if(tiempo == 0){
					tiempo = stoi(num);
					tiempos[i] = tiempo;
					num = "";
				}else if(num != "0"){
					G[i].push_back(stoi(num));
					num = "";
				}
			}else{
				num = num + linea[j];
			}
		}
		gradoEnt[i] = G[i].size();
		tiempo = 0;
	}
}

void ordenacionTopologica(void){
	
	queue<int> cola;
	while(!cola.empty())
		cola.pop();
	
	int contador = 1;
		
	// Metemos en una pila todos las tareas sin predecesores
	for(int v = 1; v <= ntareas; v++){
		cout << "Estamos en gradoEnt[v] " << gradoEnt[v] << endl;
		if(gradoEnt[v] == 0){
			cout << "cola.push(v) v -> " << v << endl; 
			cola.push(v);
		}
	}
	
	while(!cola.empty()){
		int v = cola.front();
		cout << "cola.front() " << v << endl;
		cola.pop();
		
		cout << "orden[v] antes contador " << orden[v] << endl;
		orden[v] = contador;
		
		contador++;
		cout << "orden[v] despues contador " << orden[v] << endl;

		list<int>::iterator w;
		for(w = G[v].begin(); w != G[v].end(); w++){
			cout << " ------------- WHILEEEEEEEEEE --------------- " << endl;
			cout << "estamos dentro for iterador con G[v] (*w) " << *w << endl;
			cout << "gradoEnt[*w] " << gradoEnt[*w] << endl;
			gradoEnt[*w]--;
			cout << "G[*w]-- " << gradoEnt[*w] << endl;
			if(gradoEnt[*w] == 0){
				cout << "G[*w] == 0 " <<gradoEnt[*w] << endl;
				cout << "cola.push[*w] " << endl;
				cola.push(*w);
			}
		}
	}
	
	cout << "Fuera while. Contador " << contador << endl;
	
	if (contador <= ntareas)
		cout << "IMPOSIBLE. Num tareas " << ntareas << endl;
}

void mostrarLista(void){
    list<int>::iterator EA;
    for(int i = 1; i <= ntareas; i++){
        cout << i << " -> ";
        cout << " - tiempo " << tiempos[i];
        cout << " - grado Entrada " << G[i].size() << " . Adyacentes :" ;
        
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
		mostrarLista();
		//ordenacionTopologica();
	}
}
