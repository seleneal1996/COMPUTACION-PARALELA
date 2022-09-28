#include<bits/stdc++.h>
using namespace std;
unsigned t01, t11, t02, t12;
int main(){
    int MAX;
    double A[MAX][MAX], x[MAX], y[MAX];
    vector<int> v = {100, 200, 400, 500, 800};
    for (auto MAX : v){
        cin >> MAX;
        t02 = clock();
        for(int j = 0; j < MAX; j++)//Ciclo externo
        {    
            for(int i = 0; i < MAX; i++)//Ciclo interno
            {
                y[i] += A[i][j]*x[j];
            }
        }
        t12 = clock();
        double timeBUCLE2 = (double(t12-t02)/CLOCKS_PER_SEC);
        cout << "Tiempo de ejecucion BUCLE2: " << timeBUCLE2 << endl;
    }
    return 0;
}