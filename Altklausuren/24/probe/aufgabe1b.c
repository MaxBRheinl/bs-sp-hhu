#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_COUNT 9
#define ROUNDS 3

typedef struct{
	int id;
	sem_t *sems;
	} param_t;

void *dump(void *param){
	param_t *data = (param_t*) param;
	int id = data->id;
	for(int i = 0; i < ROUNDS; i++){
		sem_wait(&data->sems[id+1]);
		printf("%d", id);
		sem_post(&data->sems[(id+2)%(THREAD_COUNT + 1)]);
		}
	return NULL;
	}

int main(){
	sem_t *sems = calloc(THREAD_COUNT + 1, sizeof(sem_t));
	if(sems == NULL){
		printf("ERROR: Allokation fehlgeschlagen.\n");
		exit(EXIT_FAILURE);
		}
	
	
	sem_init(&sems[0], 0, 1);
	for(int i = 1; i <= THREAD_COUNT; i++){
		if(sem_init(&sems[i], 0, 0)){
			printf("ERROR: Semaphore #%d konnte nicht initialisiert werden.\n", i);
			exit(EXIT_FAILURE);
			}
		}
	
	param_t *params = calloc(THREAD_COUNT, sizeof(param_t));
	if(params == NULL){
		printf("ERROR: Allokation fehlgeschlagen.\n");
		exit(EXIT_FAILURE);
		}
	for(int i = 0; i < THREAD_COUNT; i++){
		params[i].id = i;
		params[i].sems = sems;
		}
		
	pthread_t threads[THREAD_COUNT];
	for(int i = 0; i < THREAD_COUNT; i++){
		if(pthread_create(&threads[i], NULL, dump, &params[i])){
			printf("ERROR: Thread #%d konnte nicht starten.\n", i);
			exit(EXIT_FAILURE);
			}
		}
		
	for(int i = 0; i < ROUNDS; i++){
		sem_wait(&sems[0]);
		printf("M");
		sem_post(&sems[1]);
		sem_wait(&sems[0]);
		printf("\n");
		sem_post(&sems[0]);
		}
		
	for(int i = 0; i < THREAD_COUNT; i++){
		if(pthread_join(threads[i], NULL)){
			printf("ERROR: Thread #%d konnte nicht beendet werden.\n", i);
			exit(EXIT_FAILURE);
			}
		}
		
	for(int i = 0; i < THREAD_COUNT+1; i++){
		sem_destroy(&sems[i]);
		}
		
	free(sems);
	sems = NULL;
	free(params);
	params = NULL;
	exit(EXIT_SUCCESS);
	}
