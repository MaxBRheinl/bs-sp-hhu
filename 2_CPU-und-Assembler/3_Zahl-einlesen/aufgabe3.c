#include <stdio.h>
#include <stdlib.h>


#define ARR_LENGTH 10

int main() {
    char *input = malloc(ARR_LENGTH * sizeof(char));
    if (input == NULL) {
        printf("ERROR: Allokation fehlgeschlagen.\n");
        exit(EXIT_FAILURE);
    }

    printf("Geben Sie eine natuerliche Zahl ein: ");

    char c;
    int i = 0;
    while ((c = getchar()) != EOF && c != '\n') {
        if (c < '0' || '9' < c) {
            printf("Fehler: Dies ist keine natuerliche Zahl.\n");
            free(input);
            exit(EXIT_FAILURE);
        }

        if (i >= ARR_LENGTH) {
            printf("Fehler: Eingabe zu lang.\n");
            free(input);
            exit(EXIT_FAILURE);
        }

        input[i++] = c;
    }
    input[i] = '\0';

    printf("Die eingegebene Zahl ist: %s\n", input);
    free(input);
    exit(EXIT_SUCCESS);
}
