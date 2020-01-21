#******************************************************************************
# File:         makefile                                                      *
# Version:      1.0                                                           *
# Date:         2020-01-10                                                    *
# Author:       J.G. Jeronimus                                                *
# Description:  OPS Assignment 8:	                                          *
#	            Multithreading, a shared queue, mutexes and Valgrind          *
#******************************************************************************/

CXX = gcc
CXXFLAGS= -g -O0 -Wall -Wextra

EXECUTABLE = sharedQueue
SOURCES = ${filter-out main.c, ${wildcard *.c}}
HEADERS = ${wildcard *.h}
OBJECTS = ${SOURCES:.c=.o}
FILES   = character_log.txt

# Rule to create .o from .c:
%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@


.PHONY: all
all: printversion ${EXECUTABLE}

$(EXECUTABLE): $(OBJECTS) buildnumber.num
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LDXXFLAGS) -lpthread -o $@
	@cat character_log.txt
	@echo "-- Build: " $$(cat buildnumber.num)

# Create dependency file compiler option -MM
depend: $(SOURCES)
	$(CXX) $(CXXFLAGS) -MM  $^ > $@

-include depend

# Buildnumber
buildnumber.num: $(OBJECTS)
	@if ! test -f buildnumber.num; then echo 0 > buildnumber.num; fi
	@echo $$(($$(cat buildnumber.num)+1)) > buildnumber.num

# Create a clean environment
.PHONY: clean
clean:
	$(RM) $(EXECUTABLE) $(OBJECTS) $(FILES)

# Clean up dependency file
.PHONY: clean-depend
clean-depend: clean
	$(RM) depend

printversion:
	gcc --version |grep gcc

