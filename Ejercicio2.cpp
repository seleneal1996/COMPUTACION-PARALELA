#include<bits/stdc++.h>
using namespace std;

unsigned t0, t1;

void multiplication(double A[500][500],int rowsA,int columnsA,double B[500][500],int rowsB,int columnsB,double C[500][500] ){
    if(columnsA==rowsB){
        for(int i=0;i<rowsA;i++){
            for(int j=0;j<columnsB;j++){
                C[i][j]=0;
                for(int k=0;k<columnsA;k++){
                    C[i][j]=C[i][j]+A[i][k]*B[k][j];
                }
            }
        }
    }
} 

void generateArray(double M[500][500],int rows,int columns){
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            M[i][j] = rand()%5;
        }
    }
} 

int main () {
    int rowsA,columnsA,rowsB,columnsB;
    double A[500][500];
    double B[500][500];
    double C[500][500];
    vector<int> v = {100, 200, 400};
    for (auto rowsA : v){
        cout<<"A:"<<endl;
        cout<<"Ingrese FILAS de la Matriz A: ";
        cin>>rowsA;
        for (auto rowsA : v){
            cout<<"Ingrese COLUMNAS de la Matriz A: ";
            cin>>columnsA;
            generateArray(A,rowsA,columnsA);
            for (auto rowsB : v){
                cout<<"B:"<<endl;
                for (auto columnsB : v){
                    rowsB=columnsA; 
                    cout<<"ingrese COLUMNAS de la Matriz B: ";
                    cin>>columnsB;
                    generateArray(B,rowsB,columnsB);
                    t0 = clock();
                    multiplication(A,rowsA,columnsA,B,rowsB,columnsB,C);
                    t1 = clock();
                    double Time = (double(t1-t0)/CLOCKS_PER_SEC);
                    cout << "tiempo: " << Time << endl;
                }
            }
        }
    }
    return 0;
}