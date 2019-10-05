/******************************************************************************
 * File:         parent.c
 * Version:      1.2
 * Date:         2017-10-07
 * Author:       M. van der Sluys, R.B.A. Elsinghorst, J.G. Rouland
 * Description:  OPS exercise 4: forking new tasks - linear version for three processes
 ******************************************************************************/

#include <stdio.h>        // printf, perror
#include <stdlib.h>       // exit, strtoul
#include <unistd.h>       // fork, nice, execl
#include <sys/wait.h>     // wait
#include "syntaxCheck.h"

int main(int argc, char *argv[]) {
  int niceIncr;
  ErrCode err;
  
  err = SyntaxCheck(argc, argv);
  printf("%i\n", argc);
  if(err != NO_ERR) {
    DisplayError(err);
    exit(1);
  }
  
  niceIncr = (int) strtoul(argv[3], NULL, 10);
  
  switch(...) {
  case ...:  // ... failed
    perror("...");
    exit(1);
    
  case ...:  // First child process: start display from ex02 with default nice value:
    ...
    perror("...");
    exit(1);
    
  ...:  // Parent: fork a second child:
    switch(...) {
    case ...:  // ... failed
      perror("...");
      exit(1);
      
    case ...:  // Second child process: start display from ex02 with second nice value:
      ...
      ...
      perror("...");
      exit(1);
      
    ...:  // Parent: fork a third child:
      switch(...) {
      case ...:  // ... failed
        perror("...");
        exit(1);
        
      case ...:  // Third child process: start display from ex02 with third nice value:
	...
	...
	perror("...");
        exit(1);
        
      ...:  // Parent - wait for three children:
        ...
        ...
        ...
        break;
      }
      
      break;
    }
    
    break;
  }
  
  return 0;
}
