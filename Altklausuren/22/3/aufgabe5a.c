#include <stdio.h> //printf, scanf
#include <stdlib.h> //malloc, exit
#include <fcntl.h> //open
#include <unistd.h> //read


int main(){
	int fd = open("/proc/softirqs", 0);
	if(fd < 0){
		printf("ERROR: Datei konnte nicht geoeffnet werden.\n");
		exit(EXIT_FAILURE);
		}
	
	char *buffer = calloc(300, sizeof(char));
	if(buffer == NULL){
		printf("ERROR: Allokation fehlgeschlagen.\n");
		exit(EXIT_FAILURE);
		}
		
	if(read(fd, buffer, (size_t) 300) < (ssize_t)150){
		printf("ERROR: Datei konnte nicht eingelesen werden.\n");
		exit(EXIT_FAILURE);
		}
	
	close(fd);
	
	//printf("%s\n", buffer);
	int cpu0, cpu1;
	sscanf(buffer, "%*[^'X']%*s%d", &cpu0);
	sscanf(buffer, "%*[^'X']%*s%*d%d", &cpu1);
	printf("NET_TX-Interrupt (CPU0 + CPU1) = %d\n", cpu0 + cpu1);
	free(buffer);
	}
