#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <sys/time.h>
//busy waiting ***realizar un test hasta que haya un valor apropiado 
#define BARRIER_COUNT 100
//sincronizar los subprocesos para asegurar que todos esten en un mismo punto
int thread_count;
int barrier_thread_counts[BARRIER_COUNT];
pthread_mutex_t barrier_mutex;

void Usage(char* prog_name);
void *Thread_work(void* rank);

int main(int argc, char* argv[]){
	long thread, i;
	pthread_t* thread_handles = NULL; 

	if (argc != 2)
		Usage(argv[0]);
	thread_count = strtol(argv[1], NULL, 10);

	thread_handles == malloc (thread_count*sizeof(pthread_t));
	for (i = 0; i < BARRIER_COUNT; i++)
		barrier_thread_counts[i] = 0;
	pthread_mutex_init(&barrier_mutex, NULL);
	
	struct  timeval start;
   	struct  timeval end;

    //return current time  Unix Epoch
	gettimeofday(&start,NULL);
	for (thread = 0; thread < thread_count; thread++)
		pthread_create(&thread_handles[thread], NULL, Thread_work, (void*) thread);
	for (thread = 0; thread < thread_count; thread++){
		pthread_join(thread_handles[thread], NULL);
	}
	gettimeofday(&end,NULL);
    long long startusec=start.tv_sec*1000000+start.tv_usec;
    long long endusec=end.tv_sec*1000000+end.tv_usec;
    double elapsed=(double)(endusec-startusec)/1000000.0;
    printf("the result of π en %.4f seconds\n",elapsed);


	pthread_mutex_destroy(&barrier_mutex);
	free(thread_handles);
	return 0;
} /* main */

void Usage(char* prog_name){
	fprintf(stderr, "usage: %s < # threads>\n", prog_name);
	exit(0);
} /* Usage */

void *Thread_work(void* rank){
	long my_rank = (long) rank; 
	int i;
	for (i = 0; i < BARRIER_COUNT; i++){
		
		/* Barrier */
		pthread_mutex_lock(&barrier_mutex);
		barrier_thread_counts[i]++;
		pthread_mutex_unlock(&barrier_mutex);
		
		while (barrier_thread_counts[i] < thread_count);
		if (my_rank == 0){
			printf("All the threads entered the barrier %d\n", i);
			fflush(stdout);
		}
	}
	return NULL;
} /*Thread_word */