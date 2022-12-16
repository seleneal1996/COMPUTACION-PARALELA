/*El programa toma el número de subprocesos elegido por el usuario y utiliza una función aleatoria para generar un número de muestras para cada subproceso.
* El programa luego genera aleatoriamente (x, y) puntos dentro de (0.5, 0.5) y usa la estimación de Monte Carlo para encontrar pi.
* La reducción de OpenMp se usa para resumir muestras de cada subproceso.*/


#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<math.h>
#include<omp.h>

int compute_pi(int numThreads);
int main(int argc, char *argv[]){
    int numThreads=atoi(argv[1]);
    compute_pi(numThreads);
    return 0:
}

int compute_pi(int numThreads){
    double x,y,z,count,pi;
    int seed;
    int i=0;
    srand(time(NULL));
    long int samples = (int) rand()%9999999+1;
    count=0;
        #pragma omp parallel num_threads(numThreads) shared(samples) private(i,x,y,z) reduction(+:count) 
        {
            for(i=0;i<samples;i++)
            {
                x=(double)rand_r(&seed)/RAND_MAX-0.5;
                y=(double)rand_r(&seed)/RAND-MAX-0.5;
                z=x*x+y*y;
                if(z<=0.25)
                {
                    count+=1;
                }
            }
        }
        
    pi=(double)count/sample*4;
    printf("# of trinagles= %d,estimate of pi is %lf \n",samples,pi);
    return 0;
}

