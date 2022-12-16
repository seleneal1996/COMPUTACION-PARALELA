#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"
#define NUM_PUNTOS 7
#define BARRIER_COUNT 100

int thread_count;
int barrier_thread_counts[BARRIER_COUNT];
pthread_mutex_t barrier_mutex;

void Usage(char* prog_name);
void *Thread_work(void* rank);

/*--------------------------------------------------------------------*/
int main(int argc, char* argv[]) {

   //X,Y valores de los puntos a graficar
   //double valoresX[NUM_PUNTOS]={1.0, 2.0, 4.0, 8.0, 16.0, 32.0, 64.0};
   //double valoresY[NUM_PUNTOS]={0, 0, 0.1, 1.2 ,2.6 , 3.9 ,7.8};
   //FILE * archivoPuntos = fopen("puntosGraficar.txt", "w");
   /*Guardar los puntos x,y en el archivo de texto creado y abierto previamente*/
   /* for (int i=0;i<NUM_PUNTOS;i++){
      fprintf(archivoPuntos, "%lf %lf n", valoresX[i], valoresY[i]);}*/
   //fclose(archivoPuntos);
   //FILE *fp=popen("gnuplot -persist","w");fclose(fp);
   long       thread, i;
   pthread_t* thread_handles; 
   double start, finish;
   double time;

   if (argc != 2)
      Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);

   thread_handles = malloc (thread_count*sizeof(pthread_t));
   for (i = 0; i < BARRIER_COUNT; i++)
      barrier_thread_counts[i] = 0;
   pthread_mutex_init(&barrier_mutex, NULL);

   GET_TIME(start);
   for (thread = 0; thread < thread_count; thread++)
      pthread_create(&thread_handles[thread], NULL,
          Thread_work, (void*) thread);

   for (thread = 0; thread < thread_count; thread++) {
      pthread_join(thread_handles[thread], NULL);
   }
   GET_TIME(finish);

   //fprintf(fp,"plot \"puntosGraficar.txt\" with lines\n");
   //fclose(fp);
   printf("Elapsed time = %e seconds\n", finish-start);

   pthread_mutex_destroy(&barrier_mutex);
   free(thread_handles);
   return 0;
}  /* main */

void Usage(char* prog_name) {

   fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
   exit(0);
}  /* Usage */


void *Thread_work(void* rank) {
#  ifdef DEBUG
   long my_rank = (long) rank; 
#  endif
   int i;

   for (i = 0; i < BARRIER_COUNT; i++) {
      pthread_mutex_lock(&barrier_mutex);
      barrier_thread_counts[i]++;
      pthread_mutex_unlock(&barrier_mutex);
      while (barrier_thread_counts[i] < thread_count);
#     ifdef DEBUG
      if (my_rank == 0) {
         printf("All threads entered barrier %d\n", i);
         fflush(stdout);
      }
#     endif
   }

   return NULL;
}  /* Thread_work */