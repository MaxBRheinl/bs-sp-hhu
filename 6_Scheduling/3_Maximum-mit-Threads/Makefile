CC = gcc
CFLAGS = -Wall -std=gnu11 
OUTPUT = findMax

$(OUTPUT): findMax.o
	$(CC) $(CFLAGS) findMax.o -o $(OUTPUT) -lpthread
	
findMax.o: findMax.c
	$(CC) $(CFLAGS) -c findMax.c -o findMax.o
	
clean:
	rm *.o $(OUTPUT)
	
run: $(OUTPUT)
	./$(OUTPUT) 268435456 4
