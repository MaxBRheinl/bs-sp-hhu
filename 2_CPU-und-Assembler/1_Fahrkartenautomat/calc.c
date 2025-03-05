#include "stdio.h"
#include "calc.h"

int calc_coins(int value, int rest){
	int count = rest / value;
	printf("Anzahl der %d-Cent Muezen: %d\n", value, count);
	
	return rest % value;
}
