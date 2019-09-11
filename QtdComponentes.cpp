/*
*Autor: Henrique Fernandes Viana Mendes
*Data: 10/09/2019
*Programa para contar quantos componentes existem no grafo utilizando o algoritmo Busca por Profundidade
*
*Funcionamento:
*    Busca por profundidade adaptado:
*        Todos os vertices sao brancos, quando o algoritmo passa pelo vertice, ele se torna cinza
*        e comeca a passar em todos os vertices adjacentes a ele, quando todos forem verificados,
*        este se torna preto. o metodo continua ate que todos os vertices de um componente forem
*        pretos, ou seja, se ele sair do metodo e tornar a voltar, significa que existe mais de um
*        componente.
*Entrada:
*   Numero de grafos, numero de vertices, numero de arestas, 1 linha para cada aresta, indicando qual aresta eh ("a b"  -> aresta de a para b // b para a)
*/
#include <iostream>
using namespace std;

/* 
*Metodo para percorrer cada componente do grafo
*Parametros: 
*   v       = vertice atual
*   matriz  = matriz de adjacencias do grafo
*   vertice = vetor de cor de cada vertice
*   tamanho  = tamanho da matriz 
*/
void percorreMatriz(int v, int **matriz, int *vertice, int tamanho){

    vertice[v] = 1;                                             //a cor do vertice atual passa a ser cinza
    cout << (char)(v+97) << ",";                                //printa o vertice (o + 97 eh pela tabela ascii)

    for(int i = 0; i < tamanho; i++){ 
        if(matriz[v][i] == 1){                                  //se a o vertice visto for adjacente ao vertice atual,
            if(vertice[i] == 0){                                //e a cor dele for branca,
                percorreMatriz(i, matriz, vertice, tamanho);    //chama recursivamente o metodo com este vertice adjacente
            }
        }    
    }
    vertice[v] = 2;                                             //a cor do vertice em que todos os seus adjacentes ja foram percorridos vira preto
}

/*
*Metodo para criar e inicializar a matriz de adjacencias
*Parametros:
*   tamanho = tamanho da matriz
*/
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


/*
*Metodo para criar e inicializar o vetor de cores
*Parametros:
*    tamanho = tamanho do vetor ( quantidade de vertices de grafo )
*/
int* criaVetor(int tamanho){
    int* vertice = new int[tamanho];            //declaracao e inicializacao do vetor de cores do grafo              
        for(int i = 0; i< tamanho; i++){        //(0 - branco,   1 - cinza,   2 - preto) 
            vertice[i] = 0;                     //se for branco nao foi visitado, se for cinza, foi visitado mas ainda falta os
        }                                       //vertices adjacentes a ele, se for preto ja visitou ele e seus vertices adjacentes
    return vertice;                             
}


/*
*Metodo para printar a matriz de adjacencias ( nao eh utilizado no codigo )( apenas para visualizacao )
*Se quiser utiliza-lo, eh so colocar na main, depois de acrescentadas as arestas na matriz ( linha 140 nesse codigo )
*Parametros:
*   matriz = a matriz de adjacencias desejada
*   tamanho = tamanho da matriz
*/
void printMatriz(int **matriz, int tamanho){
    cout << "\n    ";
    for(int i = 0; i < tamanho; i ++) cout << (char)(97 + i) << " ";
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

/*
*Metodo para acrescentar as arestas existentes na matriz de adjacencias
*Parametros;
*   matriz = matriz de adjacencias
*   e = quantidade de arestas existentes no grafo
*/
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

        cout << "Case " << c << "#:\n";

        for(int i = 0; i < tamanho; i++){           //para cada vertice branco, entra no metodo que ira percorrer todos os vertices daquele componente
            if(vertice[i]==0){                      //se o grafo passar dessa verificacao mais de 1 vez, significa que ele tem mais de um componente
                cont++;                             //cont = quantidade de componentes
                percorreMatriz(i,matriz,vertice, tamanho);
                cout <<"\n";
            }
        }
        cout << cont << " connected components\n\n";

    c++;    
    }
    return 0;
}