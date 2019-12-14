# Makefile for OPS exercise 
# Use tabs for indentation, not spaces!

all: printversion display

# Link object files and create a binary executable:
display: 
	gcc -Wall ex01.c -o ex01
	
# Compile C-file 

clean:
	rm -f ex01
	rm -f ex01.c~
	dir -als

printversion:
	gcc --version | grep gcc

test:
	./ex01 & ./ex01 -h & ./ex01 -e test.int & ./ex01 -f test.int & ./ex01 -e test.txt & ./ex01 -f test.txt & ./ex01 -v

help:
	./ex01 -h	