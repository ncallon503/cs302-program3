# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
 
CC = g++
CFLAGS = -Wall -g
 
# ****************************************************
# Targets needed to bring the executable up to date
 
Callon-Nathan-Program3: Callon-Nathan-Program3.o Game.o Tree.o
    $(CC) $(CFLAGS) -o Callon-Nathan-Program3 Callon-Nathan-Program3.o Game.o Tree.o
 
# The main.o target can be written more simply
 
Callon-Nathan-Program3.o: Callon-Nathan-Program3.cpp Tree.h Game.h
    $(CC) $(CFLAGS) -c Callon-Nathan-Program3.cpp
 
Game.o: Game.cpp Game.h
	$(CC) $(CFLAGS) -c Game.cpp
 
Tree.o: Tree.cpp Tree.h
	$(CC) $(CFLAGS) -c Tree.cpp