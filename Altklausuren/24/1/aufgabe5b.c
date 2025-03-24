#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

typedef struct {
    pthread_mutex_t mutex;
    int counter;
} shared_data_t;


int main() {
	pid_t pid = 0;
	shared_data_t *addr = mmap(NULL, sizeof(shared_data_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, 0, 0);
	if(addr == MAP_FAILED){
		printf("ERROR: Shared-Memory konnte nicht erstellt werden.\n");
		exit(EXIT_FAILURE);
		}
		
	if(pthread_mutex_init(&addr->mutex, NULL)!=0){
		printf("ERROR: Mutex konnte nicht initialisiert werden.\n");
		munmap(addr, sizeof(shared_data_t));
		exit(EXIT_FAILURE);
		}
	
	pid = fork();
	if(pid == 0){
		for(int i = 0; i < 5; i++){
			pthread_mutex_lock(&addr->mutex);
			addr->counter++;
			pthread_mutex_unlock(&addr->mutex);
			}
		exit(EXIT_SUCCESS);
		}
		
	else if(pid > 0){
		for(int i = 0; i < 5; i++){
			pthread_mutex_lock(&addr->mutex);
			addr->counter++;
			pthread_mutex_unlock(&addr->mutex);
			}
		
		waitpid(pid, 0, 0);	
		printf("Final counter value = %d\n", addr->counter);
		pthread_mutex_destroy(&addr->mutex);
		munmap(addr, sizeof(shared_data_t));
		exit(EXIT_SUCCESS);
		}
		
	else{
		printf("ERROR: Kindprozess konnte nicht erstellt werden.\n");
		pthread_mutex_destroy(&addr->mutex);
		munmap(addr, sizeof(shared_data_t));
		exit(EXIT_FAILURE);
		}
}
