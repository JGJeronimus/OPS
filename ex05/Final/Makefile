# Makefile for OPS exercise 6: getsignal/sendsignal


# Make both programs by default:
all: getsignal sendsignal


# Link and create binary executable
getsignal: getsignal.o
	gcc -Wall -o getsignal getsignal.o

# Compile .c files to object files (.o files)
getsignal.o: getsignal.c
	gcc -c -Wall getsignal.c


# Link and create binary executable
sendsignal: sendsignal.o
	gcc -Wall -o sendsignal sendsignal.o

# Compile .c files to object files (.o files)
sendsignal.o: sendsignal.c
	gcc -c -Wall sendsignal.c


clean:
	rm -f *.o getsignal sendsignal

