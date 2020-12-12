OBJS	= main.o Otsu.o Bradley.o  ../image.o 
SOURCE	= main.c ../image.c Otsu.c Bradley.c 
HEADER	= binarization.h ../image.h
OUT	= TIBO
CC	 = gcc
CFLAGS	 = -g -c -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-variable -Wno-unused-parameter -lSDL2 -lSDL2_image -Werror -std=c99 
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
