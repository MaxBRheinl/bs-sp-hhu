#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

#define LINES              8  // Anzahl Zeilen in 'DATA'
#define CHARS_PER_LINE    12  // Anzahl Zeichen pro Zeile in 'DATA'
#define DATA              "......\\.\\..........\\.\\..........\\.\\...----------..----------.......././.......././.......././..."


int main(){
	int pipe_ends[2];
	pid_t pid = 0;
	int status;
	
	char *addr = mmap(NULL, sizeof(char) * LINES*CHARS_PER_LINE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, 0, 0);
	if(addr == MAP_FAILED){
		printf("ERROR: Shared Memory konnte nicht angelegt werden.\n");
		exit(EXIT_FAILURE);
		}
		
	if(pipe(pipe_ends)){
		perror("pipe");
		exit(EXIT_FAILURE);
		}
	
	
	pid = fork();
	
	if(pid == 0){
		printf("Child: working (transforming arrow)\n");
		for(int i = 0; i < LINES*CHARS_PER_LINE; i++){
			if(addr[i] == '.'){
				addr[i] = ' ';
				}
			}
		printf("Child: sending on pipe data ready message\n");
		write(pipe_ends[1], "ready", strlen("ready"));
		
		printf("Child: exiting\n");
		exit(EXIT_SUCCESS);
		}
		
	else if(pid > 0){
		printf("Parent: copying data into shared memory\n");
		strcpy(addr, DATA);
		printf("Parent: waiting on pipe for data ready message\n");
		char msg[5];
		if(read(pipe_ends[0], &msg, 5) < 5){
			printf("ERROR: Read konnte nicht einlesen.\n");
			exit(EXIT_FAILURE);
			}
			
		printf("Parent: dumping result\n");
		for(int i = 0; i < LINES; i++){
			for(int j = 0; j < CHARS_PER_LINE; j++){
				printf("%c", addr[(i*CHARS_PER_LINE)+j]);
				}
				printf("\n");
			}
		fflush(stdout);
		munmap(addr, sizeof(addr));
		exit(EXIT_SUCCESS);
		}
		
	else{
		printf("ERROR: Erstellung des Kindprozesses fehlgeschlagen.\n");
		exit(EXIT_FAILURE);
		}
	}
