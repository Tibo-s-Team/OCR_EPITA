OBJS	=   visual.o ../image.o  ../preprocessing/suppression_couleurs.o  ../segmentation/segmentation.o  ../segmentation/binaryTree.o  ../preprocessing/filtrage.o 
SOURCE	=   visual.c ../image.c  ../preprocessing/suppression_couleurs.c  ../segmentation/segmentation.c  ../segmentation/binaryTree.c  ../preprocessing/filtrage.c 
HEADER	=  *.h 
OUT	= OCR
CC	 = gcc
CFLAGS	 = -g -c -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-variable -Wno-unused-parameter -lSDL2 -lSDL2_image -Werror -std=c99 #$(shell pkg-config --cflags sdl ) `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
LFLAGS	 = -lSDL -lSDL_image
LDLIBS = `pkg-config --libs gtk+-3.0` -lSDL -lSDL_image
$(VERBOSE).SILENT: $(OBJS)


all: $(OBJS)
	#$(CC) -g $(OBJS) -o $(OUT) $(LDLIBS)

#visual.o: visual.c
#	$(CC) $(CFLAGS) visual.c -std=c99


#clean:
#	rm -f $(OBJS) $(OUT)

#run: $(OUT)
#	./$(OUT)
