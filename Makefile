###########################################
# Declare some Makefile variables
###########################################

CC = g++ # Compiler
LANG_STD = -std=c++17
COMPILER_FLAGS = -Wall # -Wfatal-errors #wfatal only shows first error instad of all
INCLUDE_PATH = -I"./libs/" -I/opt/homebrew/include -L/opt/homebrew/lib
SRC_FILES = ./src/*.cpp \
			./src/Game/*.cpp \
			./src/Logger/*.cpp
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.4
OBJ_NAME = 2DGameEngine

# Expand on this if windows not working?
# ifeq ($(OS),Windows NT)
# 	CC=msvc
# else

###########################################
# Declare some Makefile rules
###########################################
build:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SRC_FILES) ${LINKER_FLAGS} -o $(OBJ_NAME)

run:
	./$(OBJ_NAME)

clean:
	rm $(OBJ_NAME)
