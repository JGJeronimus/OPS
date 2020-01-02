# Makefile for OPS exercise 6: getsignal/sendsignal


# Make both programs by default:
all: getsignal_sendpid sendsignal_getpid


# Link and create binary executable
getsignal_sendpid: getsignal_sendpid.o
	gcc -Wall -o getsignal_sendpid getsignal_sendpid.o

# Compile .c files to object files (.o files)
getsignal_sendpid.o: getsignal_sendpid.c
	gcc -c -Wall getsignal_sendpid.c


# Link and create binary executable
sendsignal_getpid: sendsignal_getpid.o
	gcc -Wall -o sendsignal_getpid sendsignal_getpid.o

# Compile .c files to object files (.o files)
sendsignal_getpid.o: sendsignal_getpid.c
	gcc -c -Wall sendsignal_getpid.c


clean:
	rm -f *.o getsignal_sendpid sendsignal_getpid

