/*
Usar um algoritmo de arvore geradora minima (PRIM/Kruskal) ou Djikstra, pegar o menor caminho entre os 2 pontos, 
verificar se ainda faltam passageiros, se sim, excluir do grafo o caminho encontrado e refazer o metodo ate que todos os passageiros
tenham chegado ou ate nao ter mais caminho entre os 2 vertices desejados
*/
#include<iostream>
#include <string>
using namespace std;

void printMatriz(int **matriz, int tamanho){
    cout << "\n    ";
    for(int i = 0; i < tamanho; i ++) 
    cout << (char)(97 + i) << " ";
    cout << "\n\n";
    for(int i = 0; i < tamanho; i++){
        cout << (char)(97 + i) << "   ";           
            for(int j = 0; j < tamanho; j++){
                cout << matriz[i][j] << " ";
            }
            cout << "\n";
    }
    cout << "\n";
}

void printVetor(int* v, int tam){
    for(int i = 0; i < tam;i++){
        cout<<v[i]<<" ";
    }
    cout<<"\n";
}

int menorValor(int* v, int tamanho){

    int menor = 999999999;
    int a = 0;
    for(int i = 0; i < tamanho; i++){
        if((v[i] != -1) && (v[i] < menor)){
            menor = v[i];
            a = i;
        }
    }
    return a;     
}

int* inicializaVetor(int vertices, int valor){
    int* vet = new int[vertices];
    for(int i = 0; i < vertices; i++){
        vet[i] = valor;
    }

    return vet;
}

int Djisktra(int** matriz, int vertices){

    int* vetValores = inicializaVetor(vertices, 999999999);
    int* vetValores2 = inicializaVetor(vertices, 999999999);
    vetValores[0] = 0;
    vetValores2[0] = 0;
    int* vetPai = inicializaVetor(vertices, -1);
    int menor = 0; 
    int c = 0;
    while(c < vertices){
        for(int i = 0; i < vertices; i++){
            if((vetValores[i] != -1) && (matriz[menor][i] != -1) && (i != menor) && (vetValores[i] > vetValores[menor] + matriz[menor][i])){
                vetValores[i] = vetValores[menor] + matriz[menor][i];
                vetValores2[i] = vetValores2[menor] + matriz[menor][i];
                vetPai[i] = menor;
            }
        }
        vetValores[menor] = -1;
        menor = menorValor(vetValores, vertices);
        
        c++;
    }
    int retorno = -1;
    int soma = 0;
    int i = vertices-1;
    soma = vetValores2[vertices-1];
    while(i != -1){
        if(vetPai[i] != -1){
            matriz[vetPai[i]][i] = -1;
            matriz[i][vetPai[i]] = -1;
            i = vetPai[i];
        }else if(i == 0){
                i = -1;
                retorno = soma;
            }else {
                i = -1;
                retorno = -1;
            }
    }
    return retorno;

}

int** colocaValores(int** matriz, int arestas, int tamanho){
    
    int A,B,C;
    while(arestas > 0){

        cin >> A;
        cin >> B;
        cin >> C;

        matriz[A-1][B-1] = C;
        matriz[B-1][A-1] = C;
       
        arestas = arestas-1;
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
    matriz = colocaValores(matriz, arestas, vertices);

    return matriz;
}

int main(){

        int cidades, rotas;
        int instancia = 1;
        while(scanf("%d", &cidades) != EOF){

            cin >> rotas;

            int** matriz = criaMatriz(cidades, rotas);

            int D, K;
            cin >> D;
            cin >> K;

            int valor = 0;
            while(D > 0){
                int a = Djisktra(matriz, cidades);
                if(D > K){
                    valor = valor + a*K;
                }else valor = valor + a*D;
                D = D - K;
                if(a == -1){
                    valor = -1;
                    D = -1;
                }
            }

            cout << "Instancia " << instancia << "\n\n";

            (valor==-1) ? cout<<"impossivel\n\n\n\n" : cout << valor << "\n\n\n\n"; 
            instancia = instancia + 1;
        }
    return 0;
}