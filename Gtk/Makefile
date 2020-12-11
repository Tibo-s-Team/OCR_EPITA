OBJS	= visual.o ../src/image.o ../src/preprocessing/suppression_couleurs.o ../src/segmentation/segmentation.o ../src/segmentation/binaryTree.o ../src/preprocessing/filtrage.o 
SOURCE	= visual.c ../src/image.c ../src/preprocessing/suppression_couleurs.c ../src/segmentation/segmentation.c ../src/segmentation/binaryTree.c ../src/preprocessing/filtrage.c 
HEADER	= ../src/*.h 
OUT	= OCR
CC	 = gcc
CFLAGS	 = `pkg-config --cflags gtk+-3.0` `pkg-config --cflags sdl` -Wall -O3
LFLAGS	 = #-lSDL -lSDL_image
LDLIBS = `pkg-config --libs gtk+-3.0` `pkg-config --libs sdl` -lm -lSDL_image
$(VERBOSE).SILENT: $(OBJS)

all: $(OBJS)

main: ${OBJS}

clean:
    ${RM} ${OBJS} ${DEP} main

-include ${DEP}