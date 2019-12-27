# Makefile for OPS exercise 2
# Use tabs for indentation, not spaces!

all: printversion display

# Link object files and create a binary executable:
display: parent.o displayFunctions.o syntaxCheck.o
	gcc -Wall -o parent parent.o displayFunctions.o syntaxCheck.o

# Compile C-files and create object files (.o).
# The option -c ensures no linking takes place:
display.o: parent.c displayFunctions.h errorCodes.h
	gcc -c -Wall parent.c

displayFunctions.o: displayFunctions.c displayFunctions.h syntaxCheck.h errorCodes.h
	gcc -c -Wall displayFunctions.c

clean:
	rm -f parent.o displayFunctions.o

cleanall: clean
	rm -f parent

printversion:
	gcc --version | grep gcc
