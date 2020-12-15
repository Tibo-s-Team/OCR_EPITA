#SOURCE	= main.c src/image.c src/preprocessing/utils.c src/preprocessing/suppression_couleurs.c src/segmentation/segmentation.c src/segmentation/boundaryBox.c src/preprocessing/filtrage.c src/binarization/Bradley.c src/binarization/Otsu.c
SOURCE = main.c $(shell find ./ -name '[^mb]*.c') ./segmentation/boundaryBox.c
OBJS = $(SOURCE:.c=.o)


OUT	= TIBO
CC	 = gcc
CFLAGS	 = -g -c -Wno-format -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-variable -Wno-unused-parameter -lSDL2 -lSDL2_image `pkg-config --cflags gtk+-3.0 gmodule-2.0` -export-dynamic
LFLAGS	 = -lSDL2 -lSDL2_image -lm `pkg-config --libs gtk+-3.0 gmodule-2.0`
$(VERBOSE).SILENT: $(OBJS)


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) main.c -std=c99

clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)
