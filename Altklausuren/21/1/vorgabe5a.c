/* Klausur1: Vorgabe, Aufgabe 5.a) */

#include <stdio.h>  // Fuer fopen, fscanf, fclose, printf
#include <stdlib.h> // Fuer exit
#include <unistd.h> // Fuer sleep


int main() {
   printf("Warte 5 Sekunden, damit ein paar Thread-Umschaltungen passieren koennen ...");
   fflush(stdout);
   
   for (int i=0; i<5; i++) 
      sleep(1);
   printf("fertig!\n");

   /* Das Auslesen von /proc/mypid/sched soll hier, also nach der for-Schleife erfolgen */

}
