# Makefile

CC=gcc
CFLAGS=-W -Wall -ansi -pedantic -std=c99
HEADER= *.h
LDFLAGS=-fsanitize=address
EXEC=main

all: $(EXEC)

main: DataManipulation.o neuralnetwork.o NN_functions.o XOR.o main.o
	$(CC) -o main DataManipulation.o neuralnetwork.o NN_functions.o XOR.o main.o -lm $(LDFLAGS)

neuralnetwork.o: neuralnetwork.c
	$(CC) -o neuralnetwork.o -c neuralnetwork.c -lm $(CFLAGS)

NN_functions.o : NN_functions.c
	$(CC) -o NN_functions.o -c NN_functions.c -lm $(CFLAGS)

XOR.o : XOR.c
	$(CC) -o XOR.o -c XOR.c -lm $(CFLAGS)

DataManipulation.o : DataManipulation.c
	$(CC) -o DataManipulation.o -c DataManipulation.c -lm $(CFLAGS)

main.o: main.c $(HEADER)
	$(CC) -o main.o -c main.c -lm $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
# END
