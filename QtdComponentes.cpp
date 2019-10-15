#include <iostream>
using namespace std;

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

int** criaMatriz(int tamanho){

    int** matriz = new int*[100];                   //declaracao da matriz
        for(int i = 0; i < tamanho; i ++){            
            matriz[i] = new int[tamanho];
        }

        for(int i = 0; i < tamanho; i++){           //inicializacao da matriz com 0
            for(int j = 0; j < tamanho; j++){
                matriz[i][j] = 0;
            }
        }
    return matriz;
}

int* criaVetor(int tamanho){
    int* vertice = new int[tamanho];            //declaracao e inicializacao do vetor de cores do grafo              
        for(int i = 0; i< tamanho; i++){        //(0 - branco,   1 - cinza,   2 - preto) 
            vertice[i] = 0;                     //se for branco nao foi visitado, se for cinza, foi visitado mas ainda falta os
        }                                       //vertices adjacentes a ele, se for preto ja visitou ele e seus vertices adjacentes
    return vertice;                             
}


void acrescentaArestas(int** matriz, int e){
    while(e > 0){                               //executa para a quantidade de arestas existentes

            char x , y;                         //para cada aresta, le os dois vertices
            cin >> x;                           //e acrescenta na matriz de adjacencias
            cin >> y;
                                                //como os grafos lidos sao grafos nao orientados, acrescenta-se as arestas nos dois sentidos
            matriz[x - 97][y - 97] = 1;         //acrescenta x -> y
            matriz[y - 97][x - 97] = 1;         //acrescenta y -> x

            e--;    
        }
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

    int qtd_grafos;    
    cin >> qtd_grafos;                          //Le a quantidade de grafos a serem lidos

    int c = 1;
    
    while(c <= qtd_grafos){                     //executa o codigo para cada grafo

        int cont = 0;

        int tamanho;
        cin >> tamanho;                         //le a quantidade de vertices no grafo
        int e;                                  //e a quantidade de arestas existentes
        cin >> e;

        int** matriz = criaMatriz(tamanho);     //criacao e inicializacao da matriz

        int* vertice = criaVetor(tamanho);      //criacao e inicializacao do vetor

        acrescentaArestas(matriz, e);           //acrescenta as arestas na matriz de adjacencias

        cout << "Case #" << c << ":\n";

        for(int i = 0; i < tamanho; i++){           //para cada vertice branco, entra no metodo que ira percorrer todos os vertices daquele componente
            if(vertice[i]==0){                      //se o grafo passar dessa verificacao mais de 1 vez, significa que ele tem mais de um componente
                cont++;                             //cont = quantidade de componentes
                int* vetor = new int[tamanho];
                for(int j = 0; j < tamanho; j++){
                    vetor[j] = -1;
                }
                vetor = percorreMatriz(i,matriz,vertice, tamanho, vetor);
                ordenarVetor(vetor, tamanho);
                for(int i = 0; i < tamanho; i++){
                    if(vetor[i] != -1){
                        cout << (char)(vetor[i]+97) << ",";
                    }
                }
                cout <<"\n";
            }
        }
        cout << cont; 
        cout << " connected components\n\n";

    c++;    
    }
    return 0;
}