# Makefile for OPS exercise 4

all: printversion parent


printversion:
	gcc --version |grep gcc

# Link object files and create a binary executable
parent: parent.o syntaxCheck.o
	gcc -Wall -o parent parent.o syntaxCheck.o

# Compile C-files and create object files (.o).
# The option -c ensures no linking takes place:
parent.o: parent.c
	gcc -c -Wall parent.c

syntaxCheck.o: syntaxCheck.c
	gcc -c -Wall syntaxCheck.c

clean:
	rm -f *.o parent
