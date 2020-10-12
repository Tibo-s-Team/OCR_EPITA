OBJS	= main.o src/image.o src/preprocessing.o
SOURCE	= main.c src/image.c src/preprocessing.c
HEADER	= src/*.h 
OUT	= TIBO
CC	 = gcc
CFLAGS	 = -g -c -Wall -Wextra -lSDL2 -lSDL2_image 
LFLAGS	 = -lSDL2 -lSDL2_image

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) main.c -std=c99


clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)
