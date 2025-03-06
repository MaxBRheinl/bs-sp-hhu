CC = gcc
CFLAGS = -Wall -std=gnu11
OUTPUT = kartei

$(OUTPUT): kartei.o
	$(CC) $(CFLAGS) kartei.o -o $(OUTPUT)
	
kartei.o:
	$(CC) $(CFLAGS) -c kartei.c -o kartei.o
	
clean:
	rm *.o $(OUTPUT)

run: $(OUTPUT)
	./$(OUTPUT)
