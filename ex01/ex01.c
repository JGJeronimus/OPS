//  OPS exercise 1: argc, argv[], envp[] and getopt()

#include <getopt.h>   // getopt(), struct option
#include <stdio.h>    // file IO, perror()
#include <stdlib.h>   // exit()
#include <string.h>   // str(n)cpy()
#include <stdbool.h>  // Bool type


// Function prototypes:
void print_help();
void read_file(char *fileName, bool lastLine);
void print_env(char* envp[]);


int main(int argc, char* argv[], char* envp[]) {
  // If no arguments are given, print help:
  if( argc == 1 ) {
    printf("No arguments found.\n\n");
    print_help();
    exit(0);
  }
  
  static struct option long_options[] = {
    ...
    {0,          0,                 0, 0}
  };
  
  // Scan the different command-line arguments and options:
  while(1) {
    int opt = getopt_long(...);
    
    if(opt == -1) break;  // No more options
    
    switch(opt) {
    }
    
  }
  return 0;
}


// Print program help:
void print_help() {
  printf("Available program options:\n\
  -h --help                  Print this help and exit\n\
  -f --file <file name.txt>  Specify a text file to print the FIRST line from\n\
  -e --end  <file name.txt>  Specify a text file to print the LAST line from\n\
  -v --env                   Print environment variables\n");
}


// Read the input file.  lastLine is 0 or 1, depending on whether the first or last line should be printed:
void read_file(char *fileName, bool lastLine) {
  
  // Verify the file's extension
  char ext[5];
  strncpy(ext, fileName+strlen(fileName)-4,5);  // Get the last 4 characters of the string + \0 !
  if(strcmp(ext,".txt") != 0) {
    fprintf(stderr, "%s:  the input file should be a text file, with the extention '.txt'\n", fileName);
    return;
  }
  
  FILE *inFile = fopen(fileName, "r");  // NOTE: C stdlib fopen() rather than system call open()
  if( inFile  == NULL) {
    perror(fileName);
    return;
  }
  
  int iLine = 0;
  char line[1024], firstLine[1024];
  while( fgets(line, 1024, inFile) != NULL ) {
    iLine++;
    if(iLine==1) strncpy(firstLine, line, 1024);  // Save the first line
  }
  fclose(inFile);
  
  if(lastLine) {
    printf("The last line of the file %s reads:\n%s\n", fileName, line);
  } else {
    printf("The first line of the file %s reads:\n%s\n", fileName, firstLine);
  }
}


// Print environment variables:
void print_env(char* envp[]) {
  
  int nPar = 0;
  printf("print_env():\n");
  
  // Scan and print the different environment variables:
  while(envp[nPar]) {
    printf(...);
    nPar++;
  }
  
  printf("\n I found a total of %i environment variables.\n\n", nPar);
}
