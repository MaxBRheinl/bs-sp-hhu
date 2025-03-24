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

}
