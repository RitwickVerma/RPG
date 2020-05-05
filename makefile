CC=g++
CFLAGS=-Isource/include -lSDL2 -lSDL2_image -ltmxlite -g
SRC_DIR=./source/src
SRC_FILES=$(wildcard $(SRC_DIR)/*.cpp)
OBJ=main


all: 
	$(CC) $(CFLAGS) -o $(OBJ) $(SRC_FILES) 

run:
	./main

exec: all run

clean:
	rm -f main 