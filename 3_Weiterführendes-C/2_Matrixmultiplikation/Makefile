CC = gcc
CFLAGS = -Wall -std=gnu11
OUTPUT = matrix

$(OUTPUT): matrix.o
	$(CC) $(CFLAGS) matrix.o -o $(OUTPUT)
	
matrix.o: matrix.c
	$(CC) $(CFLAGS) -c matrix.c -o matrix.o
	
clean:
	rm *.o $(OUTPUT)

run: $(OUTPUT)
	./$(OUTPUT)
