OBJS	= main.o  neuralnetwork.o NN_functions.o OCR_NN.o 
SOURCE	= main.c  neuralnetwork.c NN_functions.c OCR_NN.c
HEADER	= src/*.h 
OUT	= IA
CC	 = gcc
CFLAGS	 = -g -c -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-variable -Wno-unused-parameter -lSDL2 -lSDL2_image -Werror -std=c99 $(shell pkg-config --cflags sdl SDL_image)  
LFLAGS	 = -lSDL2 -lSDL2_image
$(VERBOSE).SILENT: $(OBJS)


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) -lm $(LFLAGS)

main.o: main.c
	$(CC) -lm $(CFLAGS) main.c -std=c99


clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)

# END