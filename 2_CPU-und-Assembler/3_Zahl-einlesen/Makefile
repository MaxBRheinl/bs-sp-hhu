CC = gcc
CFLAGS = -Wall -std=gnu11
OUTPUT = aufgabe3

$(OUTPUT): aufgabe3.o
	$(CC) $(CFLAGS) aufgabe3.o -o $(OUTPUT)
	
aufgabe3.o: aufgabe3.c
	$(CC) $(CFLAGS) -c aufgabe3.c -o aufgabe3.o
	
clean:
	rm *.o $(OUTPUT)
	
run: $(OUTPUT)
	./$(OUTPUT)
