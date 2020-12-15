#SOURCE	= main.c src/image.c src/preprocessing/utils.c src/preprocessing/suppression_couleurs.c src/segmentation/segmentation.c src/segmentation/boundaryBox.c src/preprocessing/filtrage.c src/binarization/Bradley.c src/binarization/Otsu.c
SOURCE = main.c $(shell find -name '[^m]*.c') 
OBJS = $(SOURCE:.c=.o)


OUT	= TIBO
CC	 = gcc
CFLAGS	 = -g -c -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-variable -Wno-unused-parameter -lSDL2 -lSDL2_image `pkg-config --cflags gtk+-3.0`
LFLAGS	 = -lSDL2 -lSDL2_image -lm `pkg-config --libs gtk+-3.0`
$(VERBOSE).SILENT: $(OBJS)


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) main.c -std=c99

clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)
