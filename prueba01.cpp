#include<bits/stdc++.h>
using namespace std;

int main(){
    int MAX = 1000;
    double A[MAX][MAX], x[MAX], y[MAX];
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            y[i] += A[i][j]*x[j];

}