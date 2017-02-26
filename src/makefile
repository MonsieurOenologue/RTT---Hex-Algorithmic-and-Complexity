# Declaration of variables
CC = g++
CC_FLAGS = -w -pthread -Wall -g -std=c++11


# File names
EXEC = Hexxxor3000
SOURCES = $(wildcard *.cpp)
OBJECTS = GameController.o HexBoard.o

# Define particular targets
.PHONY: clean

# Deactivate implicit rules
.SUFFIXES:

# Obtains the OS type, either 'Darwin' (OS X) or 'Linux'
UNAME_S:=$(shell uname -s)

# Function used to check variables. Use on the command line:
# make print-VARNAME
# Useful for debugging and adding features
print-%: ; @echo $*=$($*)

# Generating the exe
all : $(EXEC)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

gameController.o: GameController.cpp HexBoard.h
		$(CC) $(CFLAGS) -o $@ -c $<

hexBoard.o: HexBoard.cpp HexBoard.h
		$(CC) $(CFLAGS) -o $@ -c $<

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
