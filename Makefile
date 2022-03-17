# the compiler: gcc for C program, define as g++ for C++
CC = g++

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

  # the build target executable:
MAIN = main
SRCS= ./sources/bishop.cpp ./sources/chess.cpp ./sources/coordinates.cpp ./sources/king.cpp ./sources/knight.cpp ./sources/main.cpp ./sources/pawn.cpp ./sources/piece.cpp ./sources/queen.cpp ./sources/rook.cpp ./sources/sprites.cpp
HEADER_DIR= ./headers
SDL2 = /usr/include/SDL2
INCLUDES = -I $(HEADER_DIR) -I $(SDL2)
LIBS = -lSDL2 -lSDL2_image
LFLAGS = -L/usr/local/lib

OBJS = $(SRCS:.c=.0)

all: $(MAIN)

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) $(TARGET)