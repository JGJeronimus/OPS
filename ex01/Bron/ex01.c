//  OPS exercise 1: Command-line parameters

// Include the needed header files
#include <stdio.h>    // file IO, perror()
#include <string.h>   // str(n)cpy()
#include <stdbool.h>  // Bool type
#include <getopt.h>   // get opt long library.
#include <stdlib.h>   // for the exit function.

// Function prototypes:
void print_help();
void read_file(char *fileName, bool lastLine);
void print_env(char* envp[]);


int main(int argc, char* argv[], char* envp[]) {

  int opt = 0;
  int help = -1;
  bool end = false;
  char file[128] = "\0";
  
  // specifying the expected options.
  // options "file" and "end" require a file name with .txt extension.
  // is end a boolean option in addition to file to switch between first and last line???
  static struct option long_options[] = {
    {"help",     no_argument,       0,     'h'  },
    {"file",     required_argument, 0,     'f'  },
    {"end",      required_argument, 0,     'e'  },
    {"env",      no_argument,       0,     'v'  },
    {0,          0,                 0,     0    }
  };

  int long_index = 0;
  while ((opt = getopt_long(argc, argv, "hf:e:v", long_options, &long_index)) != -1) {
    
    switch (opt) {
    case 'h' : help = 0;
      break;
    case 'f' : strcpy(file, optarg);
      break;
    case 'e' : end = true;
               strcpy(file, optarg);
      break;
    case 'v' : print_env(envp);
      break;
    default  : print_help();
      exit(EXIT_FAILURE);
    };
  };

  if(strcmp(file, "\0") == 0) {
    print_help();
    exit(EXIT_FAILURE);
  } else {
    read_file(file, end);
  };

  if(help == 0) {
    print_help();
  };
  
  // If no arguments are given, print help
  
  // Set up struct option array long_options[]
  
  // Scan the different command-line arguments and options
  return 0;
}


// Print program help:
void print_help() {
  printf("Available program options:\n\
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
    printf("%s\n", envp[nPar]);
    nPar++;
  }
  
  printf("\nA total of %i environment variables was found.\n\n", nPar);
}
