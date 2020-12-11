<<<<<<< HEAD
OBJS	= main.o src/image.o src/preprocessing/suppression_couleurs.o src/segmentation/segmentation.o src/segmentation/binaryTree.o src/preprocessing/filtrage.o src/binarization/Otsu.o src/binarization/Bradley.o  
SOURCE	= main.c src/image.c src/preprocessing/suppression_couleurs.c src/segmentation/segmentation.c src/segmentation/binaryTree.c src/preprocessing/filtrage.c src/binarization/Otsu.c src/binarization/Bradley.c 
HEADER	= src/*.h 
=======
OBJS	= main.o src/image.o src/preprocessing/suppression_couleurs.o src/segmentation/segmentation.o src/segmentation/boundaryBox.o src/preprocessing/filtrage.o 
SOURCE	= main.c src/image.c src/preprocessing/suppression_couleurs.c src/segmentation/segmentation.c src/segmentation/boundaryBox.c src/preprocessing/filtrage.c 

>>>>>>> 325a2fb694d9b09862640edd0a193487f93c7b60
OUT	= TIBO
CC	 = gcc
CFLAGS	 = -g -c -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-variable -Wno-unused-parameter -lSDL2 -lSDL2_image -Werror -std=c99 $(shell pkg-config --cflags sdl SDL_image)  
LFLAGS	 = -lSDL -lSDL_image
$(VERBOSE).SILENT: $(OBJS)


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) main.c -std=c99


clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)
