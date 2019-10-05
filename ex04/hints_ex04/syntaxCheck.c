/******************************************************************************
 * File:         syntaxCheck.c
 * Version:      1.1
 * Date:         2016-03-18
 * Author:       M. van der Sluys, R.B.A. Elsinghorst, J.G. Rouland
 * Description:  OPS exercise 4: function definitions for parent.c
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "syntaxCheck.h"

ErrCode SyntaxCheck(int argc, char **argv) {
  ErrCode errCode = NO_ERR;
  char *endPosition;
  if(argc != NUM_OF_PARS) {
    errCode = ERR_PARS;
  } else {
    strtoul(argv[3], &endPosition, 10);
    if(*endPosition != '\0') errCode = ERR_NICE;
    
    // Test for negative sign (-), because strtoul() can't:
    if(argv[3][0]=='-') errCode = ERR_NICE;
  }
  return errCode;
}

void DisplayError(ErrCode errCode) {
  switch(errCode) {
  case ERR_PARS:
    printf("\nNumber of command-line parameters does not equal seven.\n");
    break;
  case ERR_NICE:
    printf("\nNice increment is not a positive integer.\n");
    break;
  default:
    printf("\nUnknown error code!\n");
  }
  printf("\nCorrect syntax:\n");
  printf("  ./parent <print type> <number of times> <nice increment> <print character 1> [<print character 2>  <...>]\n\n");
  
  printf("  first parameter <print type>: e, p or w\n");
  printf("  second parameter <number of times>: positive integer\n");
  printf("  third parameter <nice increment>: positive integer\n");
  printf("  fourth parameter <print character>: a single character\n");
  printf("  optional print characters: list of space-separated single characters\n");
  printf("\n");  // Newline at end
}
