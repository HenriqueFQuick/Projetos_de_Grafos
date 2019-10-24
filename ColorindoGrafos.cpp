#include <iostream>
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

void metodo(int** matriz, int* vetCor, int qtdArestas, int vertices){
    while(qtdArestas > 0){

        for(int i = 0; i < vertices; i++){
            for(int j = 0; j < vertices; j++){
                if(vetCor[i] != vetCor[j]){
                    if(matriz[i][j] == 0){
                        matriz[i][j] = 1;
                        matriz[j][i] = 1;
                        i = vertices;
                        j = vertices;
                    }
                }
            }
        }

        qtdArestas--;
    }
}

int** colocaValores(int** matriz, int arestas, int tamanho){
    
    int A,B;
    while(arestas > 0){

        cin >> A;
        cin >> B;

        matriz[A-1][B-1] = 1;
        matriz[B-1][A-1] = 1;
       
        arestas = arestas-1;
    }
    return matriz;
}


int** inicializaMatriz(int** matriz, int vertices){
    
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            matriz[i][j] = 0;
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

int* criaVetorCores(int tamanho){
    int* cor = new int[tamanho];
    for(int i = 0; i < tamanho; i++){
        cin>>cor[i];
    }
    return cor;
}

int* criaVetor(int tamanho){
    int* vertice = new int[tamanho];            //declaracao e inicializacao do vetor de cores do grafo              
        for(int i = 0; i< tamanho; i++){        //(0 - branco,   1 - cinza,   2 - preto) 
            vertice[i] = 0;                     //se for branco nao foi visitado, se for cinza, foi visitado mas ainda falta os
        }                                       //vertices adjacentes a ele, se for preto ja visitou ele e seus vertices adjacentes
    return vertice;                             
}

int* percorreMatriz(int v, int **matriz, int *vertice, int tamanho, int* vetor){

    vertice[v] = 1;                                             //a cor do vertice atual passa a ser cinza
    //cout << (char)(v+97) << ",";                                //printa o vertice (o + 97 eh pela tabela ascii)
    vetor[v] = v;

    for(int i = 0; i < tamanho; i++){ 
        if(matriz[v][i] == 1){                                  //se a o vertice visto for adjacente ao vertice atual,
            if(vertice[i] == 0){                                //e a cor dele for branca,
                vetor = percorreMatriz(i, matriz, vertice, tamanho, vetor);    //chama recursivamente o metodo com este vertice adjacente
            }
        }    
    }
    vertice[v] = 2;                                             //a cor do vertice em que todos os seus adjacentes ja foram percorridos vira preto
    return vetor;
}


void swap(int* xp, int* yp){
    int temp = *yp;
    *xp = *yp;
    *yp = temp;
}

int* ordenarVetor(int* vetor, int tam){
    int min;
    for(int i = 0; i < tam; i++){
        min = i;
        for(int j = i+1; j < tam; j++)
            if(vetor[j] < vetor[min])
                min = j;
            swap(vetor[min], vetor[i]);
    }
}

int main(){

    int qtd;
    cin>>qtd;
    while(qtd>0){

        int N,M,P,K;
        cin>>N;
        cin>>M;
        cin>>P;
        cin>>K;

        int* cor = criaVetorCores(N);
        int** matriz = criaMatriz(N,M);

        //printMatriz(matriz, N);

        metodo(matriz,cor,P,N);

        //printMatriz(matriz, N);

        int cont = 0;
        int* vertice = criaVetor(N);      //criacao e inicializacao do vetor

        for(int i = 0; i < N; i++){           //para cada vertice branco, entra no metodo que ira percorrer todos os vertices daquele componente
            if(vertice[i]==0){                      //se o grafo passar dessa verificacao mais de 1 vez, significa que ele tem mais de um componente
                cont++;                             //cont = quantidade de componentes
                int* vetor = new int[N];
                for(int j = 0; j < N; j++){
                    vetor[j] = -1;
                }
                vetor = percorreMatriz(i,matriz,vertice, N, vetor);
                ordenarVetor(vetor, N);
            }
        }

        if(cont == 1){
            cout<<"Y\n\n";
        }else cout<<"N\n\n";

        qtd--;
    }

    return 0;
}