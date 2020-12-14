OBJS	= main.o src/image.o src/preprocessing/suppression_couleurs.o src/segmentation/segmentation.o src/segmentation/boundaryBox.o src/preprocessing/filtrage.o src/binarization/Bradley.o src/binarization/Otsu.o 
SOURCE	= main.c src/image.c src/preprocessing/suppression_couleurs.c src/segmentation/segmentation.c src/segmentation/boundaryBox.c src/preprocessing/filtrage.c src/binarization/Bradley.c src/binarization/Otsu.c

OUT	= TIBO
CC	 = gcc
CFLAGS	 = -g -c -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-variable -Wno-unused-parameter -lSDL2 -lSDL2_image 
LFLAGS	 = -lSDL2 -lSDL2_image -lm
$(VERBOSE).SILENT: $(OBJS)


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) main.c -std=c99


clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)
