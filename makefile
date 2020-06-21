CC=g++
CLIBS=-lSDL2 -lSDL2_image -ltmxlite
CFLAGS=-Isource/include -Wno-narrowing -g -std=c++17
SRC_DIR=./source/src
SRC_FILES=$(wildcard $(SRC_DIR)/*.cpp)
OBJ=main


all: 
	$(CC) $(CFLAGS) $(CLIBS) -o $(OBJ) $(SRC_FILES) 

run:
	./main

exec: all run

clean:
	rm -f main 