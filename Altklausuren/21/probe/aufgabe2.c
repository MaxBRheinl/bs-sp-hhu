#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


int run = 1;   /* 1 = running, 0 = terminate */


/* getch blockiert solange, bis eine Taste gedrueckt wird */
int getch () {
    int ch;
    struct termios tc_attrib;
    if (tcgetattr(STDIN_FILENO, &tc_attrib))
        return -1;

    tcflag_t lflag = tc_attrib.c_lflag;
    tc_attrib.c_lflag &= ~ICANON & ~ECHO;

    if (tcsetattr(STDIN_FILENO, TCSANOW, &tc_attrib))
        return -1;

    ch = getchar();

    tc_attrib.c_lflag = lflag;
    tcsetattr (STDIN_FILENO, TCSANOW, &tc_attrib);
    return ch;
}


void *player1( void *p ) {
	pthread_mutex_t *mutex = (pthread_mutex_t*) p;
	
	while(run){
		pthread_mutex_lock(&mutex[0]);
		printf("Ping\n");
		sleep(1);
		pthread_mutex_unlock(&mutex[0]);
		pthread_mutex_unlock(&mutex[1]);
		}
		
	return NULL;
}


void *player2( void *p ) {
	pthread_mutex_t	*mutex = (pthread_mutex_t*) p;
	
	while(run){
		pthread_mutex_lock(&mutex[1]);
		printf("Pong\n");
		sleep(1);
		pthread_mutex_unlock(&mutex[1]);
		pthread_mutex_unlock(&mutex[0]);
		}
		
	return NULL;
}

int main ( ) {
	pthread_mutex_t *mutex = calloc(2, sizeof(pthread_mutex_t));
	if(mutex == NULL){
		printf("ERROR: Allokation fehlgeschlagen.\n");
		exit(EXIT_FAILURE);
		}
	
	for(int i = 0; i < 2; i++){
		if(pthread_mutex_init(&mutex[i], NULL)){
			printf("ERROR: Mutex #%d konnte nicht initialisiert werden.\n", i);
			free(mutex);
			mutex = NULL;
			exit(EXIT_FAILURE);
			}
		}
		
	pthread_mutex_lock(&mutex[1]);
	
	pthread_t threads[2];
	if(pthread_create(&threads[0], NULL, player1, mutex)){
		printf("ERROR: Player1-Thread konnte nicht initialisiert werden.\n");
		pthread_mutex_destroy(&mutex[0]);
		pthread_mutex_destroy(&mutex[1]);
		free(mutex);
		mutex = NULL;
		exit(EXIT_FAILURE);
		}
 
 
	printf("Start the game\n(Press any key to stop the game)");
	if(pthread_create(&threads[1], NULL, player2, mutex)){
		printf("ERROR: Player2-Thread konnte nicht initialisiert werden.\n");
		pthread_mutex_destroy(&mutex[0]);
		pthread_mutex_destroy(&mutex[1]);
		free(mutex);
		mutex = NULL;
		exit(EXIT_FAILURE);
		}
		
	getch();
	run = 0;
	
	printf("A key was pressed, end of game.\n");
	
	for(int i = 0; i < 2; i++){
		if(pthread_join(threads[i], NULL)){
			printf("ERROR: Thread #%d konnte nicht beendet werden.\n", i);
			pthread_mutex_destroy(&mutex[0]);
			pthread_mutex_destroy(&mutex[1]);
			free(mutex);
			mutex = NULL;
			exit(EXIT_FAILURE);
			}
		}
		
	for(int i = 0; i < 2; i++){
		pthread_mutex_destroy(&mutex[i]);
		}
		
	free(mutex);
	mutex = NULL;
	exit(EXIT_SUCCESS);	
}
