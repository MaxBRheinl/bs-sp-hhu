#include <stdio.h>
#include <stdlib.h>
#include "calc.h"


int main(){
	int amount;
	int values[] = {50, 20, 5, 2, 1};
	
	printf("Geben Sie den Geldbetrag in Cent ein: ");
	if(scanf("%d", &amount) != 1){
		printf("Ungueltige Eingabe!\n");
		exit(EXIT_FAILURE);
	}
	
	for(int i = 0; i < 5; i++){
		amount = calc_coins(values[i], amount);
	}
	
	exit(EXIT_SUCCESS);
}
