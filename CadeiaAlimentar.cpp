#include <iostream>
#include <stdbool.h>
using namespace std;

int menorValor(int* v, int tamanho){
    int menor = 999999999;
    int a = 0;
    for(int i = 0; i < tamanho; i++){
        if((v[i] != -1) && v[i] < menor){
            menor = v[i];
            a = i;
        }
    }
    return a;     
}

bool dijkstra(int vertice, int tamanho, int** matriz){
    int* d = new int[tamanho];
    int* pai = new int[tamanho];

    for(int i = 0; i < tamanho; i++){
        d[i] = pai[i] = 999999999;
    }
    d[vertice] = 0;
    pai[vertice] = -1;

    int c = 0;
    while(c  < tamanho){

        int menor = menorValor(d, tamanho);
        for(int i = 0; i < tamanho; i++){
            if((d[i] != -1) && (i != menor) && (matriz[menor][i] != 0) && (matriz[menor][i]+d[menor] < d[i])){
                d[i] = matriz[menor][i]+d[menor];
            }
        }
        d[menor] = -1;

        for(int j = 0; j < tamanho; j++){
            if(d[j] == 999999999){
                int c2 = 0;
                int* dist = new int[tamanho];
                for(int i = 0; i < tamanho; i++){
                    dist[i] = 999999999;
                }
                dist[j] = 0;
                while(c2 < tamanho){
                    int menor2 = menorValor(dist, tamanho);
                    for(int i = 0; i < tamanho; i++){
                        if((dist[i] != -1) && (i != menor2) && (matriz[menor2][i] != 0) && (matriz[menor2][i]+dist[menor2] < dist[i])){
                            dist[i] = matriz[menor2][i]+dist[menor2];
                        }
                    }
                    dist[menor2] = -1;
                    c2++;
                    int menor3 = menorValor(dist, tamanho);
                    if(dist[menor3] == 999999999) c2 = tamanho;
                }
                if(dist[menor] == 999999999){
                        return false;
                }
            }
        }
        c++;
    }
    return true;
}

void inicializaMatriz(int** matriz, int relacoes, int tam){ 

    
    while(relacoes > 0){ 
        int a, b;    
        cin >> a;
        cin >> b;
        
        matriz[a-1][b-1] = 1;
   
        relacoes--;
    }

}

int** CriaMatriz(int tamanho){
    int** matriz = new int*[100];
    for(int i = 0; i < tamanho; i++){
        matriz[i] = new int[tamanho];
    }
    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            matriz[i][j] = 0;
        }
    }
    return matriz;
}

int main(){

    int vertices, relacoes;
    cin >> vertices;
    cin >> relacoes;

        int** matriz = CriaMatriz(vertices); 
        inicializaMatriz(matriz, relacoes, vertices);
        /*for(int i = 0; i < vertices; i++){
            for(int j = 0; j < vertices; j++){
                cout << matriz[i][j] << " ";
            }
            cout << "\n";
        }*/

        bool resultDjk = dijkstra(0,vertices,matriz);
        if(resultDjk){
            cout << "Bolada";
        }else cout << "Nao Bolada";


    return 0;
}