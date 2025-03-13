CC = gcc
CFLAGS = -Wall -std=gnu11 
OUTPUT = pcomp

$(OUTPUT): pcomp.o matrix.o
	$(CC) $(CFLAGS) pcomp.o matrix.o -o $(OUTPUT) -lpthread
    
pcomp.o: pcomp.c
	$(CC) $(CFLAGS) -c pcomp.c -o pcomp.o
    
matrix.o: matrix.c
	$(CC) $(CFLAGS) -c matrix.c -o matrix.o
    
clean:
	rm *.o $(OUTPUT)
    
run: $(OUTPUT)
	sudo ./$(OUTPUT) 512 512 4
