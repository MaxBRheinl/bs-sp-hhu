/* Klausur1: Vorgabe, Aufgabe 5.a) */

#include <stdio.h>  // Fuer fopen, fscanf, fclose, printf
#include <stdlib.h> // Fuer exit
#include <unistd.h> // Fuer sleep
#include <fcntl.h>


int main() {
   printf("Warte 5 Sekunden, damit ein paar Thread-Umschaltungen passieren koennen ...");
   fflush(stdout);
   
   for (int i=0; i<5; i++) 
      sleep(1);
   printf("fertig!\n");

   /* Das Auslesen von /proc/mypid/sched soll hier, also nach der for-Schleife erfolgen */
   pid_t pid = getpid();
   char filepath[50];
   
   snprintf(filepath, sizeof(filepath), "/proc/%d/sched", pid);
   int fd = open(filepath, 0);
   if(fd == -1){
	   printf("ERROR: Datei konnte nicht geoeffnet werden.\n");
	   exit(EXIT_FAILURE);
	   }
	   
	char *buff = calloc(600, sizeof(char));
	if(buff == NULL){
		printf("ERROR: Allokation fehlgeschlagen.\n");
		exit(EXIT_FAILURE);
		}
	if(read(fd, buff, 600) <= 450){
		free(buff);
		buff=NULL;
		printf("ERROR: Datei konnte nicht eingelesen werden.\n");
		exit(EXIT_FAILURE);
		 }
	//printf("%s\n", buff);
	
	int switches;
	sscanf(buff, "%*[^'w']%*s%*s%d", &switches);


	printf("nr_switches = %d\n", switches);
	
	free(buff);
	exit(EXIT_SUCCESS);
}
