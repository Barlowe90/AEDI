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
bool visitado[MAX];		// Marcas de nodos visitados
string linea;
string num = "";
//queue<int> cola;
int tiempo = 0;
int tiempos[1000];
	
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
		
//	memset(tiempos, 0, sizeof(tiempos));
	
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
		tiempo = 0;
	}
}

//void bpp(int v){
	//visitado[v]= true;
	
	//for (int w = 0; w < ntareas; w++)
		//if (!visitado[w] && G[v][w])
			//bpp(w);
//}

//void busquedaPP (void){
	//memset(visitado, 0, sizeof(visitado));
	
	//for (int v = 0; v < ntareas; v++)
		//if (!visitado[v])
			//bpp(v);
	//cout << endl;
//}

void mostrarLista(void){
    list<int>::iterator EA;
    for(int i = 1; i <= ntareas; i++){
        cout << i << " -> ";
        cout << " - tiempo " << tiempos[i] << " . " ;
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
	
	for (int i = 0; i < ncasos; i++) {
		leeGrafo();
		//busquedaPP();
		mostrarLista();
	}
}
