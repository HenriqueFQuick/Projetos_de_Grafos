/*
Usar um algoritmo de arvore geradora minima (PRIM/Kruskal) ou Djikstra, pegar o menor caminho entre os 2 pontos, 
verificar se ainda faltam passageiros, se sim, excluir do grafo o caminho encontrado e refazer o metodo ate que todos os passageiros
tenham chegado ou ate nao ter mais caminho entre os 2 vertices desejados
*/
#include<iostream>
using namespace std;

int* inicializaVetor(int vertices, int valor){
    int* vet = new int[vertices];
    for(int i = 0; i < vertices; i++){
        vet[i] = valor;
    }
    return vet;
}

int Djisktra(int** matriz, int vertices){
    int* vetValores = inicializaVetor(vertices, 999999999);
    int* vetPai = inicializaVetor(vertices, -1);
    

}

int** colocaValores(int** matriz, int arestas){
    
    int A,B,C;
    while(arestas > 0){

        cin >> A;
        cin >> B;
        cin >> C;

        matriz[A][B] = C;

        arestas--;
    }
    return matriz;
}


int** inicializaMatriz(int** matriz, int vertices){
    
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            matriz[i][j] = -1;
        }
    }    
    return matriz;
}

int** criaMatriz(int vertices, int arestas){

    int** matriz = new int*[100];
    
    for(int i = 0; i < vertices; i++){
        matriz[i] = new int[vertices];
    }

    matriz = inicializaMatriz(matriz, vertices);
    matriz = colocaValores(matriz, arestas);

    return matriz;
}

int main(){

    int cidades, rotas;
    cin >> cidades;
    cin >> rotas;

    int instancia = 1;

    int** matriz = criaMatriz(cidades, rotas);

    int D, K;
    cin >> D;
    cin >> K;

    int valor = -1;
    while(D > 0){
        valor = Djisktra(matriz, cidades);
        D -= K;
    }

    cout << "Instancia " << instancia;

    (valor=-1) ? cout<<"impossivel\n" : cout<<valor<<"\n"; 

    return 0;
}