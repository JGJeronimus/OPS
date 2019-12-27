//  OPS exercise 1: Command-line parameters

#include <getopt.h>   // getopt(), struct option
#include <stdio.h>    // printf(), file IO, perror()
#include <stdlib.h>   // exit()
#include <string.h>   // str(n)cpy()
#include <stdbool.h>  // Bool type

// Function prototypes:
void print_help(void);
void read_file(char *fileName, bool lastLine);
void print_env(char* envp[]);


int main(int argc, char* argv[], char* envp[]) {
  int  options = 0;
  char txtfile[128] = "\0";
  bool lastLine = false;
  bool printHelp = false;
  //helpPrinted = -1;
  
  // Set up struct option array long_options[]----> See "print_help"
  static struct option long_options[] = {
         {"end",      required_argument, 0, 'e'},
         {"file",     required_argument, 0, 'f'},
         {"help",     no_argument,       0, 'h'},
         {"env",      no_argument,       0, 'v'},
         {0,          0,                 0,  0 }
       };

  // Scan the different command-line arguments and options
  
  int long_index = 0;
  while ((options = getopt_long(argc, argv, "hf:e:v" , long_options, &long_index)) != -1) {

  switch(options) {
  case 'e' : lastLine = true; strcpy(txtfile, optarg);      // display the last line of a *.txt file
      break;
  case 'f' : strcpy(txtfile, optarg);                       // display the first line of a *.txt file
      break;
  case 'h' : print_help(); exit(EXIT_SUCCESS);              // display help:
      break;
  case 'v' : print_env(envp); exit(EXIT_SUCCESS);           // enviroment variables
      break;
  default  : print_help(); exit(EXIT_SUCCESS);              // If no arguments are given, print help
                                           
    };
  };

  if(strcmp(txtfile, "\0") == 0) {
     /*printf("het ligt aan regel 50\n"); */ print_help();
     exit(EXIT_FAILURE);
     }
    else {
    read_file(txtfile, lastLine);
   }
  
 if(printHelp == true) {
     print_help();
     }
  
  return 0;
  }

// Print program help:
void print_help() {
  printf("\nAvailable program options:\n\
  -h --help                  Print this help and exit\n\
  -f --file <file name.txt>  Specify a text file and print its FIRST line\n\
  -e --end  <file name.txt>  Specify a text file and print its LAST line\n\
  -v --env                   Print environment variables\n\n");
}
 

// Read the input file.  lastLine is 0 or 1, depending on whether the first or last line should be printed:
void read_file(char *fileName, bool lastLine) {

  // Verify the file's extension
  char ext[5];
  strncpy(ext, fileName+strlen(fileName)-4,5);  // Get the last 4 characters of the string + \0 !
  if(strcmp(ext,".txt") != 0){
    fprintf(stderr, "\n %s:  the input file should be a text file, with the extention '.txt'\n\n", fileName);
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
    printf("The last line of the file %s reads:\n\n %s \n\n", fileName, line);
  } else {
    printf("The first line of the file %s reads:\n\n %s \n\n", fileName, firstLine);
  }
}


// Print environment variables:
void print_env(char* envp[]) {

  int nPar = 0;
  printf("print_env():\n");

  // Scan and print the different environment variables:
  while(envp[nPar]) {
    printf("%s\n", envp[nPar]);
    nPar++;
  }

  printf("\nA total of %i environment variables was found.\n\n", nPar);
}
