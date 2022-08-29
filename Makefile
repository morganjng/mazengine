##
# mazengine
#
# @file
# @version 0.1

CC = g++

RM = rm

FLAGS = -Wall -Werror

LIBS = $(shell pkg-config --libs --cflags sdl2 SDL2_mixer SDL2_image yaml-cpp ncurses)

HEADERS = include/*.h

SRCS = src/*.cpp

INCLUDES = --include-directory=include/

all:

compile:
	$(CC) $(FLAGS) -c $(SRCS) $(LIBS) $(INCLUDES)
	mv *.o bin/

clean:
	$(RM)

# end
