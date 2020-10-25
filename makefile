OBJS	= main.o src/image.o src/preprocessing/suppression_couleurs.o src/segmentation/segmentation.o src/segmentation/binaryTree.o src/preprocessing/filtrage.o 
SOURCE	= main.c src/image.c src/preprocessing/suppression_couleurs.c src/segmentation/segmentation.c src/segmentation/binaryTree.c src/preprocessing/filtrage.c 
HEADER	= src/*.h 
OUT	= TIBO
CC	 = gcc
CFLAGS	 = -g -c -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-variable -Wno-unused-parameter -lSDL2 -lSDL2_image 
LFLAGS	 = -lSDL2 -lSDL2_image
$(VERBOSE).SILENT: $(OBJS)


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) main.c -std=c99


clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)
