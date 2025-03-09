CC = gcc
CFLAGS = -Wall -std=gnu11
OUTPUT = einlesen

$(OUTPUT): einlesen.o
	$(CC) $(CFLAGS) einlesen.o -o $(OUTPUT)
	
einlesen.o: einlesen.c
	$(CC) $(CFLAGS) -c einlesen.c -o einlesen.o
	
clean:
	rm *.o $(OUTPUT)
	
run: $(OUTPUT)
	./$(OUTPUT)
