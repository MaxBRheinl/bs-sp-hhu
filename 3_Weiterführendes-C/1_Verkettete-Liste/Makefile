CC = gcc
CFLAGS = -Wall -std=gnu11
OUTPUT = list

$(OUTPUT): list.o
	$(CC) $(CFLAGS) list.o -o $(OUTPUT)
	
list.o: list.c
	$(CC) $(CFLAGS) -c list.c -o list.o
	
clean:
	rm *.o $(OUTPUT)
	
run: $(OUTPUT)
	./$(OUTPUT) 20 10
