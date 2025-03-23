#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdint.h>


typedef struct {
	int start;
	int end;
	int *arr;
	} param_t;

void* find_max(void *param){
	param_t *data = (param_t*) param;
	int max, curr = data->arr[data->start];
	
	for(int i = data->start; i < data->end; i++){
		curr = data->arr[i];
		if(max < curr){
			max = curr;
			}
		}
	
	return (void*) (intptr_t) max;
	}

void fill_array(int *arr, int len){
	for(int i = 0; i < len; i++){
		arr[i] = rand();
		}
	}

int main(int argc, char* argv[]){
	if(argc != 3){
		printf("Ungueltige Eingabe. Erwartet: <Laenge des Arrays> <Anzahl der Threads>\n");
		exit(EXIT_FAILURE);
		}
	
	int arr_length;
	int thread_count;
	sscanf(argv[1], "%d", &arr_length);
	sscanf(argv[2], "%d", &thread_count);
	
	if(arr_length < 0 || arr_length & (arr_length - 1)){
		printf("Ungueltige Arraylaenge.\n");
		exit(EXIT_FAILURE);
		}
	
	if(thread_count < 0 || thread_count > 16 || thread_count & (thread_count - 1)){
		printf("Ungueltige Anzahl an Threads.\n");
		exit(EXIT_FAILURE);
		}
	
	printf("Initialisiere Array.\n");
	int *array = calloc(arr_length, sizeof(int));
	if(array == NULL){
		printf("ERROR: Allokation fehlgeschlagen.\n");
		exit(EXIT_FAILURE);
		}
		
	srand(time(NULL));
	fill_array(array, arr_length);
	
	param_t *thread_params = calloc(thread_count, sizeof(param_t));
	if(thread_params == NULL){
		printf("ERROR: Allokation fehlgeschlagen.\n");
		exit(EXIT_FAILURE);
		}
	
	int chunk_size = arr_length / thread_count;
	for(int i = 0; i < thread_count; i++){
		thread_params[i].start = i * chunk_size;
		thread_params[i].end = (i + 1) * chunk_size;
		thread_params[i].arr = array;
		}
	
	struct timespec start;
	clock_gettime(CLOCK_MONOTONIC, &start);
	printf("Initialisiere Threads.\n");
	
	pthread_t *threads = calloc(thread_count, sizeof(pthread_t));
	if(threads == NULL){
		printf("ERROR: Allokation fehlgeschlagen.\n");
		exit(EXIT_FAILURE);
		}
		
	for(int i = 0; i < thread_count; i++){
		if(pthread_create(&threads[i], NULL, find_max, &thread_params[i])){
			printf("ERROR: Thread #%d konnte nicht erstellt werden.\n", i);
			exit(EXIT_FAILURE);
			}
		}
		
	int maximum = 0;
	for(int i = 0; i < thread_count; i++){
		intptr_t thread_max;
		if(pthread_join(threads[i], (void**) &thread_max)){
			printf("ERROR: Thread #%d konnte nicht beendet werden.\n", i);
			}
		if(maximum < (int) thread_max){
			maximum = (int) thread_max;
			}
		}
		
	struct timespec end;
	clock_gettime(CLOCK_MONOTONIC, &end);
	
	printf("Berechnung abgeschlossen.\n");
	printf("Laufzeit: %ld.%09ld Sekunden.\n", end.tv_sec-start.tv_sec, end.tv_nsec-start.tv_nsec);
	printf("Maximum: %d\n", maximum);
	
	free(array);
	array = NULL;
	free(thread_params);
	thread_params = NULL;
	free(threads);
	threads = NULL;
	
	exit(EXIT_SUCCESS);	
	}
