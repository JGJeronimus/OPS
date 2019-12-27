/******************************************************************************
 * File:         displayFunctions.c
 * Version:      1.4
 * Date:         2018-02-20
 * Author:       M. van der Sluys, J.H.L. Onokiewicz, R.B.A. Elsinghorst, J.G. Rouland
 * Description:  OPS exercise 2:  function definitions for display.c
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "displayFunctions.h"
#include "syntaxCheck.h"

// Check the command-line parameters:
ErrCode SyntaxCheck(int argc, char **argv) {
  ErrCode errCode = NO_ERR; 
  if(argc < NUM_OF_PARS) {                              // Test whether the number of arguments is a minimum of 5
    errCode = ERR_PARS;
  } else {
    //errCode = TestType(argv[1]);                        // Test whether argument 1 has the correct value (print type)
    //if(errCode == NO_ERR) errCode = TestNr(argv[2]);    // Test whether argument 2 contains a positive integer (number of times)
    if(errCode == NO_ERR) errCode = TestNr(argv[3]);    // Test whether argument 2 contains an integer (nice increment)
    //if(errCode == NO_ERR) errCode = TestChar(argv[4]);  // Test whether argument 3 contains only one character (print character)
  }
  return errCode;
}

// Exercise 4C: Print only an error message for ERR_PARS and ERR_NICE:

void DisplayError(ErrCode errCode) {
  switch(errCode) {
  case ERR_PARS:
    printf("\n\tNumber of command-line parameters is less than five.\n");
    break;
  case ERR_NR:
    printf("\n\tNice Increment is not an integer.\n");
    break;
  default:
    printf("\n\tUnknown error code!\n");
  }
  
  printf("\n\tCorrect syntax:\n");
  printf("\t./parent <print type> <number of times> <nice increment> <print character>\n\n");
  //printf("\tfirst parameter:   <print type>:      e, p or w\n");
  //printf("\tsecond parameter:  <number of times>: positive integer\n");
  printf("\tthird parameter:   <nice increment>:  an integer\n");
  //printf("\tfourth parameters: <print character>: character(s) to be printed\n");
  printf("\n");  // Newline at end
}


// Print chacacter printChar numberOfTimes times using method printMethod:
/*void PrintCharacters(char printMethod, unsigned long numberOfTimes, int niceIncr, char printChar) {
  unsigned long index = 0;
  char echoCommand[] = "/bin/echo -n  ";
  
  switch(printMethod) {
  case 'e':
    echoCommand[13] = printChar;  // Put character to be printed in string
    for(index = 0; index < numberOfTimes; index++) {
      system(echoCommand);
    }
    break;
  case 'p':
    for(index = 0; index < numberOfTimes; index++) {
      printf("%c", printChar);
    }
    break;
  case 'w':
    for(index = 0; index < numberOfTimes; index++) {
      write(1, &printChar, 1);
    }
    break;
  default:
    printf("INTERNAL ERROR: Unknown print type:  %s.  This should not happen!\n", &printMethod);
  }
} */
