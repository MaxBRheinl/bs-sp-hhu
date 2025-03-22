#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


#define NUM_WORKER      4 // Muss Zweierpotenz (2, 4, 8, ...) sein
#define ARRAY_LEN    4096 // Muss durch NUM_WORKER teilbar sein
#define Z              42 // Die betrachtete Zahl muss zwischen 0 und 255 liegen

typedef struct{
	int *arr;
	int start;
	int end;
	} param_t;
	
typedef struct{
	int sm;
	int eq;
	int gr;
	} output_t;

void* calc(void* param){
	param_t *data = (param_t*) param;
	output_t *ret = malloc(sizeof(output_t));
	if(ret == NULL){
		printf("ERROR: Allokation fehlgeschlagen.\n");
		//korrekter exit?
		exit(EXIT_FAILURE);
		}
	ret->sm = 0;
	ret->eq = 0;
	ret->gr = 0;
	for(int i = data->start; i < data->end; i++){
		if(data->arr[i] < Z){
			ret->sm++;
			}
		if(data->arr[i] == Z){
			ret->eq++;
			}
		if(data->arr[i] > Z){
			ret->gr++;
			}
		}
		
	return (void*) ret;
	}

int main(){
	srand(time(NULL));
	int arr[ARRAY_LEN];
	for(int i = 0; i < ARRAY_LEN; i++){
		arr[ARRAY_LEN] = rand() % 255;
		}
	
	param_t *params = calloc(NUM_WORKER, sizeof(param_t));
	if(params == NULL){
		printf("ERROR: Allokation fehlgeschlagen.\n");
		exit(EXIT_FAILURE);
		}
		
	for(int i = 0; i < NUM_WORKER; i++){
		params[i].arr = arr;
		params[i].start = i * (ARRAY_LEN/NUM_WORKER);
		params[i].end = (i+1) * (ARRAY_LEN/NUM_WORKER);
		}
	
	pthread_t threads[NUM_WORKER];
	for(int i = 0; i < NUM_WORKER; i++){
		if(pthread_create(&threads[i], NULL, calc, &params[i])){
			printf("ERROR: Thread #%d konnte nicht erstellt werden.\n", i);
			//free(params);?
			exit(EXIT_FAILURE);
			}
		}
	
	int sm_count, eq_count, gr_count = 0;
	void *ret;
	output_t *out;
	for(int i = 0; i < NUM_WORKER; i++){
		if(pthread_join(threads[i], &ret)){
			printf("ERROR: Thread #%d konnte nicht beendet werden.\n", i);
			//free(params);?
			exit(EXIT_FAILURE);
			}
		out = (output_t*) ret;
		sm_count += out->sm;
		eq_count += out->eq;
		gr_count += out->gr;
		free(ret);
		}
		
	printf("Z = %d\n", Z);
	printf("%d ist %dmal in dem Array vorhanden\n", Z, eq_count);
	printf("%d Zahlen sind kleiner als %d\n", sm_count, Z);
	printf("%d Zahlen sind groesser als %d\n", gr_count, Z);
	
	free(params);
	params = NULL;
	exit(EXIT_SUCCESS);
	}
