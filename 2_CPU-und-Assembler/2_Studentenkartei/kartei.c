#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARR_LENGTH 10

typedef struct student{
	int id;
	char name[10];
	float note;
	} student_t;
	

int main(){
	char *name = "Student";
	student_t *kartei = malloc(ARR_LENGTH * sizeof(student_t));
	if(kartei == NULL){
		printf("ERROR: Allokation fehlgeschlagen.\n");
		exit(EXIT_FAILURE);
		}
	
	for(int i = 0; i < ARR_LENGTH; i++){
		kartei[i].id = i;
		
		strcpy(kartei[i].name, name);
		//kartei[i].name[7] = '0' + i;
		*((char*)(kartei + i) + sizeof(int) + 7) = '0' + i;
		//kartei[i].name[8] = '\0';
		*((char*)(kartei + i) + sizeof(int) + 8) = '\0';
		
		kartei[i].note = i%6 + 1;
		}
	
	for(int i = 0; i < ARR_LENGTH; i++){
		printf("Name: %s, ID: %d, Note: %.1f\n", kartei[i].name, kartei[i].id, kartei[i].note);
		}
		
	
	free(kartei);
	exit(EXIT_SUCCESS);
	}
