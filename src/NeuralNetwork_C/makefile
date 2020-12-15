# Makefile

# CC=gcc
# CFLAGS=-W -Wall -ansi -pedantic -std=c99
# HEADER= *.h
# LDFLAGS=-fsanitize=address $(shell pkg-config --cflags sdl SDL_image)
# EXEC=main

# all: $(EXEC)

# main: neuralnetwork.o NN_functions.o main.o
# 	$(CC) -o main neuralnetwork.o ../image.o NN_functions.o main.o -lm $(LDFLAGS)

# neuralnetwork.o: neuralnetwork.c
# 	$(CC) -o neuralnetwork.o -c neuralnetwork.c -lm $(CFLAGS)

# NN_functions.o : NN_functions.c
# 	$(CC) -o NN_functions.o -c NN_functions.c -lm $(CFLAGS)

# image.o : ../image.c
# 	$(CC) -o ../image.o -c ../image.c -lm $(CFLAGS)

# main.o: main.c $(HEADER)
# 	$(CC) -o main.o -c main.c -lm $(CFLAGS)

# clean:
# 	rm -rf *.o

# mrproper: clean
# 	rm -rf $(EXEC)
OBJS	= main.o ../image.o ../preprocessing/suppression_couleurs.o ../segmentation/segmentation.o ../segmentation/binaryTree.o ../preprocessing/filtrage.o neuralnetwork.o NN_functions.o OCR_NN.o DataManipulation.o
SOURCE	= main.c ../image.c ../preprocessing/suppression_couleurs.c ../segmentation/segmentation.c ../segmentation/binaryTree.c ../preprocessing/filtrage.c neuralnetwork.c NN_functions.c OCR_NN.c DataManipulation.c
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