#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>


#define BUFF_SIZE     3
#define NR_OF_ITEMS   9


char buffer[BUFF_SIZE];


void* producer(void* data) {
	sem_t *sem = (sem_t*) data;
	for(int i = 0; i < NR_OF_ITEMS; i++){
		sem_wait(&sem[0]);
		printf("Producing %d ...\n", i+1);
		buffer[i%BUFF_SIZE] = i+1;
		sem_post(&sem[1]);
		}
	return NULL;
}


void* consumer(void* data) {
	sem_t *sem = (sem_t*) data;
	for(int i = 0; i < NR_OF_ITEMS; i++){
		sem_wait(&sem[1]);
		printf("... Consuming %d\n", buffer[i%BUFF_SIZE]);
		sem_post(&sem[0]);
		}
	return NULL;
}


int main (int argc, const char* argv[]) {
	sem_t *sem = calloc(2, sizeof(sem_t));
	if(sem == NULL){
		printf("ERROR: Allokation fehlgeschlagen.\n");
		exit(EXIT_FAILURE);
		}
	sem_init(&sem[0], 0, BUFF_SIZE);
	sem_init(&sem[1], 0, 0);
	
	pthread_t threads[2];
	if(pthread_create(&threads[0], NULL, producer, sem)){
		printf("ERROR: Producer-Thread konnte nicht gestartet werden.\n");
		exit(EXIT_FAILURE);
		}
	if(pthread_create(&threads[1], NULL, consumer, sem)){
		printf("ERROR: Consumer-Thread konnte nicht gestartet werden.\n");
		exit(EXIT_FAILURE);
		}
		
	for(int i = 0; i < 2; i++){
		if(pthread_join(threads[i], NULL)){
			printf("ERROR: Thread konnte nicht beendet werden.\n");
			exit(EXIT_FAILURE);
			}
		sem_destroy(&sem[i]);
		}
	
	free(sem);
	sem = NULL;
	exit(EXIT_SUCCESS);
}
