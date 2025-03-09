#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	int fd = open("/proc/meminfo", 0);
	if(fd == -1){
		printf("ERROR: Datei konnte nicht geoefnnet werde.\n");
		exit(EXIT_FAILURE);
		}
		
	char *buff = calloc(1000, sizeof(char));
	if(buff == NULL){
		printf("ERROR: Allokation fehlgeschlagen.\n");
		exit(EXIT_FAILURE);
		}
		
	if(read(fd, buff, 1000) <= 200){
		printf("ERROR: Es konnten nicht genug Bytes eingelesen werden.\n");
		}
	
	if(close(fd) == -1){
		printf("ERROR: Datei konnte nicht geschlossen werden.\n");
		exit(EXIT_FAILURE);
		}
		
	int mem_total;
	int mem_free;
	int cached;
	
	sscanf(buff, "%*s%d", &mem_total);
	sscanf(buff, "%*[^'\n']%*s%d", &mem_free);
	sscanf(buff, "%*[^'C']%*s%d", &cached);
	
	//printf("%s\n", buff);
	printf("MemTotal: %d kB\n", mem_total);
	printf("MemFree: %d kB\n", mem_free);
	printf("Cached: %d kB\n", cached);
	
	free(buff);
	buff = NULL;
	
	exit(EXIT_SUCCESS);
	}
