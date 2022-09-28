#include<bits/stdc++.h>
using namespace std;
unsigned t0, t1;

void blockMultiplication(double A[500][500],double B[500][500],double C[500][500], int MAX ){
    int N = MAX/10;
    for(int i1=0; i1<MAX; i1+=N){
        for(int i2=0; i2<MAX; i2+=N){
            for(int i3=0; i3<MAX; i3+=N){
                int I1 =  min(i1 + N, MAX);
                for (int i = i1; i < I1; ++i){
                    int I2 = min(i2 + N, MAX);
                    for (int j = i2; j < I2; ++j){
                        int I3 =min(i3 + N, MAX);
                        for (int k = i3; k < I3; ++k){
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }    
} 

void generateArray(double M[500][500],int f,int c){
    for(int i=0;i<f;i++){
        for(int j=0;j<c;j++){
            M[i][j] = rand()%51;
        }
    }
} 

int main () {
    
    int MAX;
    double A[500][500];
    double B[500][500];
    double C[500][500];
    vector<int> v = {100, 200, 400};
    for (auto MAX : v){
        cin>>MAX;
        generateArray(A,MAX,MAX);
        generateArray(B,MAX,MAX);
        t0 = clock();
        blockMultiplication(A,B,C,MAX);
        t1 = clock();
        double Time = (double(t1-t0)/CLOCKS_PER_SEC);
        cout << "tiempo: " << Time << endl;
    }
    return 0;
}