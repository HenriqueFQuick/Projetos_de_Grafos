#include <iostream>
#include <cmath>
using namespace std;


/*
*Metodo para printar a matriz de que possui as distancias entre cada ponto ( nao eh utilizado no codigo )( apenas para visualizacao )
*Se quiser utiliza-lo, eh so colocar na main, depois de criar a matriz ( linha 110 nesse codigo )
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
*Metodo para retornar o menor valor no vetor desejado
*Parametros:
*   v = vetor desejado
*   tamanho = tamanho do vetor
*/
double menorValor(double* v, int tamanho){
    double menor = 999999999.0;
    int a = 0;
    for(int i = 0; i < tamanho; i++){
        if((v[i] != -1) && v[i] < menor){
            menor = v[i];
            a = i;
        }
    }
    v[a] = -1;
    return menor;     
}

/*
*MEtodo para inicializar o vetor a ser utilizado no algoritmo
*(Todos os valores iguais a 999999999.0 e o primeiro iguall a -1)
*Parametros:
*   tamanho = tamanho do vetor
*/
double* inicializaVetor(int tamanho){
    double* vet = new double[tamanho];
    for(int i = 0 ; i < tamanho; i++){
        vet[i] = 999999999.0;                                                   //Inicializa o vetor colocando 999999999 em cada posicao
    }
    vet[0] = -1;                                                                //Na posicao 0 eh colocado -1 para indicar que eh o comeco
    return vet;
}

/*
*Metodo para calcular a AGM(Arvore Geradora Minima) e retornar seu peso
*Parametros:
*   tamanho = tamanho da matriz e do vetor
*   **matrizDistancia = matriz contendo as distancias entre cada vertice do grafo
*/
double PRIM(int tamanho, double** matrizDistancia){
    double* vet = inicializaVetor(tamanho);                                     //Inicializo o vetor
    int c = 0;
    double contador = matrizDistancia[0][0];
    while(c < tamanho-1){
        for(int i = 0; i < tamanho; i ++){
            if((c != i)&&(vet[i] != -1)){
                if(matrizDistancia[c][i] < vet[i]){
                    vet[i] = matrizDistancia[c][i];
                }
            }
        }
        double menor = menorValor(vet, tamanho);                                //Pegar o menor valor do vetor
        contador = contador + menor;                                            //Incrementar o contador com o peso do vertice adicionado na AGM
        c++;
    }
    return contador;
}

/*
*Metodo para criar e inicializar a matriz de distancias utilizada no algoritmo
*Parametros:
*   *x = ponteiro para o vetor com os valores de x de cada ponto
*   *y = ponteiro para o vetor com os valores de y de cada ponto
*   tamanho = tamanho da matriz
*/
double** criaMatriz(int* x, int* y, int tamanho){
    double** matriz = new double*[100];                                         

    for(int i = 0; i < tamanho; i ++){            
        matriz[i] = new double[tamanho];                                        //Cria a matriz
    }

    for(int i = 0; i < tamanho; i++){           
        for(int j = 0; j < tamanho; j++){
            matriz[i][j] = sqrt(pow((x[j] - x[i]), 2)+pow((y[j] - y[i]),2));    //Inicializa a matriz com as distancias de cada ponto
        }                                                                       //Sendo calcladas com a formula sqrt((X2-X1)^2 + (Y2-Y1)^2)
    }                                                                           //(Distancia entre 2 pontos do plano cartesiano)
    return matriz;
}

/*
*Metodo para criar os vetores com os valores de X e Y de cada ponto lido
*Parametros:
*   *x = ponteiro para o vetor com os valores de x de cada ponto
*   *y = ponteiro para o vetor com os valores de y de cada ponto
*   tamanho = tamanho da matriz
*/
void criaVetor(int* x, int* y, int tamanho){

    for(int i = 0; i < tamanho; i ++){
        int a, b;
        cin >> a;                                               //Le os valores de X para cada ponto
        cin >> b;                                               //Le os valores de Y para cada ponto

        x[i] = a;                                               //Atribui os valores de X no seu vetor
        y[i] = b;                                               //Atribui os valores de Y no seu vetor
    }
}


int main(){

    int qtdCasos = 0;
    cin >> qtdCasos;                                            //Le a quantidade de casos a serem descritos

    while(qtdCasos > 0){

        int qtdPessoas = 0;
        cin >> qtdPessoas;                                      //Para cada caso, le a quantidade de pessoas(vertices)

        int* x = new int[qtdPessoas];                           //Cria um vetor para guardar os valores de x de cada ponto
        int* y = new int[qtdPessoas];                           //Cria um vetor para guardar os valores de y de cada ponto

        criaVetor(x,y, qtdPessoas);                             //Inicializa os vetores com os valores de X e Y de cada ponto lido

        double** matrizDistancia = criaMatriz(x,y,qtdPessoas);  //Cria e inicializa a matriz com as distancias entre cada ponto

        double contador = PRIM(qtdPessoas, matrizDistancia);    //Metodo adaptado do PRIM para retornar a distancia da AGM(Arvore Geradora Minima) encontrada

        cout.precision(2);
        cout << fixed << (contador/100) << "\n";                        //Print da distancia total

        qtdCasos--;
    }

    return 0;
}