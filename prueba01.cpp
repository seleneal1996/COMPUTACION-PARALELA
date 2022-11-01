#include<bits/stdc++.h>
using namespace std;
unsigned t01, t11, t02, t12;

int main()
{
    int MAX;
    double A[MAX][MAX], x[MAX], y[MAX];
    vector<int> v = {100, 200, 400, 500, 800};
    for (auto MAX : v){
        cin >> MAX ;
        t01 = clock();
        for(int i = 0; i < MAX; i++)//Ciclo externo
        {    
            for(int j = 0; j < MAX; j++)//Ciclo interno
            {
                y[i] += A[i][j]*x[j];
            }
        }
        t11 = clock();
        double timeBUCLE1 = (double(t11-t01)/CLOCKS_PER_SEC);
        cout << "Tiempo de ejecucion BUCLE1: " << timeBUCLE1 << endl;
    }
    return 0;
}