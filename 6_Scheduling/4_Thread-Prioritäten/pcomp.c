#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <limits.h>
#include <time.h>
#include "matrix.h"

typedef struct {
	uint64_t *mat_a;
	uint64_t *mat_b;
	int rows;
	int cols;
	} param_t;
	
void set_prio(pthread_t id, int policy, int prio){
	struct sched_param param;
	param.sched_priority = prio;
	
	if(pthread_setschedparam(id, policy, &param) != 0){
		printf("ERROR: Konnte Prioritaet nicht setzen.\n");
		pthread_exit((void*) id);
		}
	}

void* calc(void *param){
	param_t *data = (param_t*) param;
	uint64_t *mat_a = data->mat_a;
	uint64_t *mat_b = data->mat_b;
	int rows = data->rows;
	int cols = data->cols;
	
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);
	uint64_t *mat_c = calloc(rows * cols, sizeof(uint64_t));
	if(mat_c == NULL){
		printf("ERROR: Allokation fehlgeschlagen.\n");
		exit(EXIT_FAILURE);
		}
		
	multiplyMatrices(mat_a, mat_b, mat_c, rows, cols);
	clock_gettime(CLOCK_MONOTONIC, &end);
	
	long *time = malloc(sizeof(long));
	if(time == NULL){
		printf("ERROR: Allokation fehlgeschlagen.\n");
		exit(EXIT_FAILURE);
		}
		
	*time = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec)/ 1000 / 1000;
	free(mat_c);
	mat_c = NULL;
	
	return (void*) time;
	}

int main(int argc, char* argv[]){
	if(argc != 4){
		printf("Ungueltige Eingabe. Erwartet: <Anzahl Rows> <Anzahl Cols> <Anzahl Threads>");
		exit(EXIT_FAILURE);
		}
	
	int rows, cols, thread_count;
	
	sscanf(argv[1], "%d", &rows);
	if(rows < 0 || rows > INT_MAX){
		printf("Ungueltige Anzahl Rows.\n");
		exit(EXIT_FAILURE);
		}
	
	sscanf(argv[2], "%d", &cols);
	if(cols < 0 || cols > INT_MAX){
		printf("Ungueltige Anzahl Cols.\n");
		exit(EXIT_FAILURE);
		}
		
	sscanf(argv[3], "%d", &thread_count);
	if(thread_count < 0 || thread_count > 16){
		printf("Ungueltige Anzahl Threads.\n");
		exit(EXIT_FAILURE);
		}
		
	printf("Initializing...\n");
	uint64_t *mat_a = calloc(rows * cols, sizeof(uint64_t));
	if(mat_a == NULL){
		printf("ERROR: Allokation fehlgeschlagen.\n");
		exit(EXIT_FAILURE);
		}
		
	uint64_t *mat_b = calloc(rows * cols, sizeof(uint64_t));
	if(mat_b == NULL){
		printf("ERROR: Allokation fehlgeschlagen.\n");
		exit(EXIT_FAILURE);
		}
	
	srand(time(NULL));
	initializeMatrix(mat_a, rows, cols);
	initializeMatrix(mat_b, cols, rows);
	
	printf("Starting threads...\n");
	param_t *data = malloc(sizeof(param_t));
	if(data == NULL){
		printf("ERROR: Allokation fehlgeschlagen.\n");
		exit(EXIT_FAILURE);
		}
	data->mat_a = mat_a;
	data->mat_b = mat_b;
	data->rows = rows;
	data->cols = cols;
	
	pthread_t *threads = calloc(thread_count, sizeof(pthread_t));
	if(threads == NULL){
		printf("ERROR: Allokation fehlgeschlagen.\n");
		exit(EXIT_FAILURE);
		}
		
	for(int i = 0; i < thread_count; i++){
		if(pthread_create(&threads[i], NULL, calc, data) != 0){
			printf("ERROR: Thread #%d konnte nicht gestartet werden.\n", i);
			exit(EXIT_FAILURE);
			}
		}
		
	set_prio(threads[thread_count - 1], SCHED_FIFO, 99);
	
	long max = 0;
	long min = INT_MAX;
	int max_idx = -1;
	int min_idx = -1;
	long value;
	void *ret = NULL;
	for(int i = 0; i < thread_count; i++){
		pthread_join(threads[i], &ret);
		value = *((long*) ret);
		printf("Thread #%d finished: %ld ms\n", i, value);
		
		if(value > max){
			max = value;
			max_idx = i;
			}
			
		if(value < min) {
			min = value;
			min_idx = i;
			}
		free(ret);
		}
	ret = NULL;
	
	printf("Slowest Thread was thread #%d: %ld ms\n", max_idx, max);
	printf("Fastest Thread was thread #%d: %ld ms\n", min_idx, min);
	
	free(mat_a);
	mat_a = NULL;
	free(mat_b);
	mat_b = NULL;
	free(data);
	data = NULL;
	
	exit(EXIT_SUCCESS);
	}
