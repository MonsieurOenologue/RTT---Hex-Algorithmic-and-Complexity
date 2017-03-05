# Declaration of variables
CC = g++
CC_FLAGS = -w -pthread -Wall -g -std=c++11

# File names
EXEC = Hexxxor3000.exe
SOURCES = $(wildcard *.cpp)
OBJECTS = GameController.o HexBoard.o Action.o

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
	$(CC) $(OBJECTS) -o $(EXEC)

GameController.o: GameController.cpp HexBoard.h Action.h
		$(CC) $(CFLAGS) -o $@ -c $<

HexBoard.o: HexBoard.cpp HexBoard.h
		$(CC) $(CFLAGS) -o $@ -c $<

Action.o: Action.cpp Action.h
		$(CC) $(CFLAGS) -o $@ -c $<

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
cleanall:
	$(RM) $(EXEC) $(OBJECTS)
