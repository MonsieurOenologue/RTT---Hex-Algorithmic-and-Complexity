# Makefile
CC = g++
CFLAGS = -Wall
EXEC_NAME = Hex
OBJ_FILES = gameController.o hexBoard.o

# Définition des cibles particulières
.PHONY: clean

# Désactivation des règles implicites
.SUFFIXES:

# Création de l'exécutable
all : $(EXEC_NAME)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES)

gameController.o: gameController.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

hexBoard.o: hexBoard.cpp hexBoard.h
	$(CC) $(CFLAGS) -o $@ -c $<

# Suppression des fichiers temporaires
clean:
	rm $(EXEC_NAME) $(OBJ_FILES)