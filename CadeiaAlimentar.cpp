#include <iostream>
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

void dijkstra(int vertice, int tamanho, int** matriz, int inicial){
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
                pai[i] = menor;
            }
        }
        d[menor] = -1;
        c++;
    }
    for(int j = 0; j < tamanho; j++){
        if(d[j] != -1){
            

        }
    }
}

void inicializaMatriz(int** matriz, int relacoes){
    while(relacoes > 0){

        int a,b;
        cin >> a;
        cin >> b;

        matriz[a][b] = 1;

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
    while(relacoes > 0){

        int** matriz = CriaMatriz(vertices);

        relacoes--;
    }

    return 0;
}