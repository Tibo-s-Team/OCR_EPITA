BIN = filtrage.out

SOURCE = main.c filtrage.c utils.c suppression_couleurs.c ../image.c ../binarization/Otsu.c ../binarization/Bradley.c
OBJS = ${SOURCE:.c=.o}

CC = gcc
CFLAGS	 = -g -c -std=c99 -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-variable -Wno-unused-parameter -lSDL2 -lSDL2_image 
LFLAGS	 = -lSDL2 -lSDL2_image -lm

.PHONY: clean

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(BIN) $(LFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) main.c -std=c99

clean: 
	rm -f ${BIN} ${OBJS}

run:main.o
	./${BIN}  ../../tests/images/samples/*
