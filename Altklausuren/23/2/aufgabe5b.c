#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>


#define CARS_TO_D   3
#define CARS_TO_NE  2

sem_t sems[4];
int d = 0;
int n = 0;
typedef struct {
	int id;
	} param_t;

/* car going to Duesseldorf */
void *going_to_duesseldorf(void *param){
	param_t *data = (param_t*) param;
	int id = data->id;
	printf("NE->D [%d]: waiting\n", id%CARS_TO_D);
	
	sem_wait(&sems[3]);
	d++;
	if(d == 1){
		sem_wait(&sems[0]);
		}
	sem_post(&sems[3]);
	
	sem_wait(&sems[1]);
	printf("NE->D [%d]: on bridge\n", id%CARS_TO_D);
	sem_post(&sems[1]);
	
	sem_wait(&sems[3]);
	d--;
	if(d == 0){
		sem_post(&sems[0]);
		}
	sem_post(&sems[3]);
	
	printf("NE->D [%d]: arrived\n", id%CARS_TO_D);
	return NULL;
}

/* car going to Neuss */
void *going_to_neuss(void *param){
	param_t *data = (param_t*) param;
	int id = data->id;
	printf("D->NE [%d]: waiting\n", id%CARS_TO_NE);
	sem_wait(&sems[0]);
	sem_wait(&sems[2]);
	n++;
	if(n == 1){
		sem_wait(&sems[1]);
		}
	sem_post(&sems[2]);
	sem_post(&sems[0]);
	printf("D->NE [%d]: on bridge\n", id%CARS_TO_NE);
	sem_post(&sems[2]);
	n--;
	if(n == 0){
		sem_post(&sems[1]);
		}
	sem_post(&sems[0]);
	printf("D->NE [%d]: arrived\n", id%CARS_TO_NE);
	return NULL;
	
}


int main(){
	fflush(stdout);
	
	for(int i = 0; i < 4; i++){
		if(sem_init(&sems[i], 0, 1)){
			printf("ERROR: Semaphor konnte nicht initialisiert werden.\n");
			exit(EXIT_FAILURE);
			}
		}
		
	int count_cars = CARS_TO_D + CARS_TO_NE;
	pthread_t threads[count_cars];
	
	param_t *params = calloc(count_cars, sizeof(param_t));
	if(params == NULL){
		printf("ERROR: Allokation fehlgeschlagen.\n");
		sem_destroy(&sems[0]);
		sem_destroy(&sems[1]);
		exit(EXIT_FAILURE);
		}
	for(int i = 0; i < count_cars; i++){
		
		params[i].id = i;
		}
	
	for(int i = 0; i < CARS_TO_D; i++){
		
		if(pthread_create(&threads[i], NULL, going_to_duesseldorf, &params[i])){
			printf("ERROR: Thread #%d konnte nicht gestartet werden\n", i);
			exit(EXIT_FAILURE);
			}
		}
	for(int i = 0; i < CARS_TO_NE; i++){
		if(pthread_create(&threads[i+CARS_TO_D], NULL, going_to_neuss, &params[i+CARS_TO_D])){
			printf("ERROR: Thread #%d konnte nicht gestartet werden\n", i);
			exit(EXIT_FAILURE);
			}
		}
		
	for(int i = 0; i < count_cars; i++){
		if(pthread_join(threads[i], NULL)){
			printf("ERROR: Thread #%d konnte nicht beendet werden.\n", i);
			exit(EXIT_FAILURE);
			}
		}
	
	for(int i = 0; i < 4; i++){
		sem_destroy(&sems[i]);
		}
	free(params);
	params = NULL;
	
	exit(EXIT_SUCCESS);
}
