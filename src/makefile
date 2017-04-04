# Declaration of variables
CC = g++

INCLUDES = -I$(glfw_inc) -I$(glad_inc)
LIBRARIES = -L$(glfw_lib)

glfw = C:/MinGW
glfw_inc = $(glfw)/include/GLFW
glfw_lib = $(glfw)/lib

glad = C:/MinGW
glad_inc = $(glad)/include/glad

GL_FLAGS = -ggdb -O3 $(INCLUDES)
GL_LIBS = $(LIBRARIES) -lglfw3 -lopengl32 -lglu32 -lgdi32
CC_FLAGS = -Wall -Wextra -fexceptions -std=c++11 -pthread $(GL_FLAGS)

# File names
EXEC = Hexxxor3000.exe
SOURCES = $(wildcard *.cpp)
OBJECTS = GameController.o HexBoard.o Action.o glad.o

# Define particular targets
.PHONY: cleanall

# Disable implicit rules
.SUFFIXES:

# Obtains the OS type : 'Windows_NT', 'Darwin' (OS X) or 'Linux'
ifeq ($(OS),Windows_NT)
    OS_TYPE := Windows
    RM := del -f
else
    OS_TYPE := $(shell uname -s)
    RM := rm -f
endif

# Function used to check variables. Use on the command line:
# make print-VARNAME
# Useful for debugging and adding features
print-%: ; @echo $*=$($*)

# Generating the exe
all : $(EXEC)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) $(GL_LIBS)

GameController.o: GameController.cpp HexBoard.h Action.h
		$(CC) $(CC_FLAGS) -o $@ -c $<

HexBoard.o: HexBoard.cpp HexBoard.h
		$(CC) $(CC_FLAGS) -o $@ -c $<

Action.o: Action.cpp Action.h
		$(CC) $(CC_FLAGS) -o $@ -c $<

glad.o: glad.c
		$(CC) $(CC_FLAGS) -o $@ -c $<

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
cleanall:
	$(RM) $(EXEC) $(OBJECTS)
