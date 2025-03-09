CC = gcc
CFLAGS = -Wall -std=gnu11
OUTPUT = fork

$(OUTPUT): fork.o
	$(CC) $(CFLAGS) fork.o -o $(OUTPUT)

fork.o : fork.c
	$(CC) $(CFLAGS) -c fork.c -o fork.o

clean:
	rm *.o $(OUTPUT)
	
run: $(OUTPUT)
	./$(OUTPUT)
