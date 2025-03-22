#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>


#define BUFF_SIZE    3
#define NR_OF_ITEMS  9

char buffer[BUFF_SIZE];


void* producer(void* data) {
	sem_t *sem = (sem_t*) data;
	for(int i=1; i <= NR_OF_ITEMS; i++){
		sem_wait(&sem[0]);
		buffer[(i-1)%BUFF_SIZE] = i;
		printf("Producing %d ...\n", i);
		sem_post(&sem[1]);
		}
}


void* consumer(void* data) {
	sem_t *sem = (sem_t*) data;
	for(int i=1; i <= NR_OF_ITEMS; i++){
		sem_wait(&sem[1]);
		printf("... Producing %d\n", buffer[(i-1)%BUFF_SIZE]);
		sem_post(&sem[0]);
		}
}


int main (int argc, const char* argv[]) {		
	sem_t sem[2];
	
	if(sem_init(&sem[0], 0, BUFF_SIZE)){
		printf("Semaphore A konnte nicht erstellt werden.\n");
		exit(EXIT_FAILURE);
		}
		
	if(sem_init(&sem[1], 0, 0)){
		printf("Semaphore B konnte nicht erstellt werden.\n");
		exit(EXIT_FAILURE);
		}
		
	pthread_t threads[2];
	
	if(pthread_create(&threads[0], NULL, producer, sem)){
		printf("ERROR: Producer Thread konnte nicht erstellt werden.\n");
		exit(EXIT_FAILURE);
		}
		
	if(pthread_create(&threads[1], NULL, consumer, sem)){
		printf("ERROR: Consumer Thread konnte nicht erstellt werden.\n");
		exit(EXIT_FAILURE);
		}
		
	for(int i = 0; i < 2; i++){
		if(pthread_join(threads[i], NULL)){
			printf("ERROR: Thread #%d konnte nicht beendet werden.\n",i);
			exit(EXIT_FAILURE);
			}
		}
	sem_destroy(&sem[0]);
	sem_destroy(&sem[1]);
	exit(EXIT_SUCCESS);
}
