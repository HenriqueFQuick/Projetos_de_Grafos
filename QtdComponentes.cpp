#include <iostream>
using namespace std;

void metodo(int v, int **matriz, int vertice[], int n){

    vertice[v] = 1;
    cout << (char)(v+97) << ",";
    //cout << sizeof(matriz[v]) << "\n\n";

    for(int i = 0; i < n; i++){
        if(matriz[v][i] == 1){
            if(vertice[i] == 0){
                metodo(i, matriz, vertice, n);
            }
        }    
    }

    vertice[v] = 2;
    
}

int main(){

    int qtd, c = 1;
    cin >> qtd;
    
    while(c <= qtd){

        int n, cont = 0;
        cin >> n;

        int e;
        cin >> e;

        int** matriz = new int*[500];
        for(int i = 0; i < n; i ++){
            matriz[i] = new int[n];
        }

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                matriz[i][j] = 0;
            }
        }


        while(e > 0){

            char x , y;
            cin >> x;
            cin >> y;

            matriz[x - 97][y - 97] = 1;
            matriz[y - 97][x - 97] = 1;

            e--;    
        }

        /*for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cout << matriz[i][j] << " ";
            }
            cout << "\n";
        }*/

        int vertice[n];

        for(int i = 0; i< n; i++){
            vertice[i] = 0;
        }

        cout << "Case " << c << "#:\n";

        for(int i = 0; i < n; i++){
            if(vertice[i]==0){
                cont++;
                metodo(i,matriz,vertice, n);
                cout <<"\n";
            }
        }
        cout << cont << " connected components\n";

    c++;    
    }
    return 0;
}