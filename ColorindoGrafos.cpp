#include <iostream>
using namespace std;


/*
*Metodo para printar a matriz de que possui as distancias entre cada ponto ( nao eh utilizado no codigo )( apenas para visualizacao )
*Se quiser utiliza-lo, eh so colocar na main, depois de criar a matriz ( linha 192 nesse codigo )
*Parametros:
*   matriz = a matriz de adjacencias desejada
*   tamanho = tamanho da matriz
*/
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

bool verificaMatriz(int** m1, int**m2, int vertices){
    bool teste = true;
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            if(m1[i][j] != m2[i][j]) teste = false;
        }
    }
    return teste;
}

int** copiaMatriz(int** matriz, int vertices){
    int** m = new int*[100];
    for(int i = 0; i < vertices; i++){
        m[i] = new int[vertices];
    }
    
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            m[i][j] = matriz[i][j];
        }
    }

    return m;
}


/*
*Metodo para adicionar n arestas no grafo com a condicao de nao poder adicionar mais cores aos vertices
*/
bool metodo(int** matriz, int* vetCor, int qtdArestas, int vertices){

    int** m = copiaMatriz(matriz, vertices);

    while(qtdArestas > 0){

        for(int i = 0; i < vertices; i++){
            for(int j = 0; j < vertices; j++){              //para uma dupla de vetores i j
                if(vetCor[i] != vetCor[j]){                 //verifica se a cor dos 2 eh igual, se n for
                    if(matriz[i][j] == 0){                  //verifica se ja existe uma aresta entre eles, se n
                        matriz[i][j] = 1;                   //adiciona a aresta
                        matriz[j][i] = 1;
                        i = vertices;
                        j = vertices;
                    }
                }
            }
        }

        qtdArestas--;
    }
    return verificaMatriz(matriz, m, vertices);
}



/*
*Metodo para colocar as adjacencias na matriz (baseada na leitura do usuario)
*Parametros:
*   **matriz = ponteiro para a matriz desejada
*   arestas = quantidade de arestas necessarias para adicionar
*   tamanho = tamanho da matriz
*/
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

/*
*Metodo para inicializar a matriz de adjacencias com 0
*Parametros:
*   **matriz = ponteiro para a matriz existente
*   vertices = quantidade de vertices existentes no grafo e na matriz
*/
int** inicializaMatriz(int** matriz, int vertices){
    
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            matriz[i][j] = 0;
        }
    }    
    return matriz;
}


/*
*Metodo para a criacao e inicializacao da matriz de adjacencias
*Parametros:
*   vertices = quantidade de vertices existentes na matriz
*   arestas = quantidade de arestas necessarias para a matriz
*/
int** criaMatriz(int vertices, int arestas){

    int** matriz = new int*[100];
    
    for(int i = 0; i < vertices; i++){
        matriz[i] = new int[vertices];
    }

    matriz = inicializaMatriz(matriz, vertices);        //inicializa a matriz com 0
    matriz = colocaValores(matriz, arestas, vertices);  //coloca as adjacencias na matriz

    return matriz;
}


/*
*Metodo para criar um vetor de cores com as entradas fornecidas
*Parametros:
*   tamanho = tamanho do vetor desejado para a criacao
*/
int* criaVetorCores(int tamanho){
    int* cor = new int[tamanho];
    for(int i = 0; i < tamanho; i++){
        cin>>cor[i];
    }
    return cor;
}

/*
*Metodo para inicializar o vetor a ser utilizado no algoritmo
*(Todos os valores iguais a 0)
*Parametros:
*   tamanho = tamanho do vetor
*/
int* criaVetor(int tamanho){
    int* vertice = new int[tamanho];            //declaracao e inicializacao do vetor de cores do grafo              
        for(int i = 0; i< tamanho; i++){        //(0 - branco,   1 - cinza,   2 - preto) 
            vertice[i] = 0;                     //se for branco nao foi visitado, se for cinza, foi visitado mas ainda falta os
        }                                       //vertices adjacentes a ele, se for preto ja visitou ele e seus vertices adjacentes
    return vertice;                             
}

int* percorreMatriz(int v, int **matriz, int *vertice, int tamanho, int* vetor){

    vertice[v] = 1;                                             //a cor do vertice atual passa a ser cinza
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


/*
*Metodo para ordenar o vetor desejados
*Parametros:
*   *vetor = ponteiro para o vetor desejado para a ordenacao
*   tam = tamanho do vetor enviado como parametro
*/
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
        cin>>N;                                 //qtd de vertices
        cin>>M;                                 //qtd de arestas
        cin>>P;                                 //qtd de arestas a serem adicionadas
        cin>>K;                                 //qtd de cores existentes

        int* cor = criaVetorCores(N);           //cria o vetor coms as cores de cara vertice
        int** matriz = criaMatriz(N,M);         //cria a amtriz de adjacencias
        if(metodo(matriz,cor,P,N)){
            cout<<"N\n\n";
        }else{
            int cont = 0;
            int* vertice = criaVetor(N);            //criacao e inicializacao do vetor

            for(int i = 0; i < N; i++){             //para cada vertice branco, entra no metodo que ira percorrer todos os vertices daquele componente
                if(vertice[i]==0){                  //se o grafo passar dessa verificacao mais de 1 vez, significa que ele tem mais de um componente
                    cont++;                         //cont = quantidade de componentes
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
        }
        qtd--;
    }

    return 0;
}