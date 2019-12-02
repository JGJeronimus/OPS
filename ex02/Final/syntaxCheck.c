/******************************************************************************
 * File:         syntaxCheck.c
 * Version:      1.4
 * Datum:        2018-02-20
 * Author:       M. van der Sluys, J.H.L. Onokiewicz, R.B.A. Elsinghorst, J.G. Rouland
 * Description:  OPS exercise 2:  definitions of test functions for display.c
 ******************************************************************************/

#include <stdlib.h>
#include "syntaxCheck.h"
#include <string.h>
#include <stdio.h>


// Test whether an argument is one character long and has the correct value (e,p,w):

ErrCode TestType(char *printMethod) {
  ErrCode fout = NO_ERR;
   
  char argChar[] = "t";
  argChar[0] = *printMethod;

  if (argChar[0] != 'e' && argChar[0] != 'p' && argChar[0] != 'w')  { // single character in argument must be either an 'e', 'p' or 'w' ,('f'<-----schrijfvaud boek?)
    fout = ERR_TYPE;
  }
  
  return fout;
}


// Test whether an argument contains a non-negative number:
ErrCode TestNr(char *numberOfTimes) {
  ErrCode fout = NO_ERR;
  
  char testNumber[128] = "T";                 //hoeveel is dat?
  strcpy(testNumber, numberOfTimes );
  int numTimes = atoi(testNumber);

  if (numTimes < 1) {                                                    //  test for unsigned int && >0
    fout = ERR_NR;
  }

  return fout;
}


// Test whether an argument contains only one character:
ErrCode TestChar(char *printChar) {
  ErrCode fout = NO_ERR;
  
  int stringLength = strlen(printChar);
  
  if(stringLength != 1){    //  single char
    fout = ERR_CHAR;
  }

  
  return fout;
}

/*
  NO_ERR    No syntax error occurred in the command line
  ERR_PARS  The number of command-line parameters is not equal to 4
  ERR_TYPE  The print type is incorrect (not one of 'e', 'p' or 'w')
  ERR_NR    The number is not a positive integer
  ERR_CHARS The print text contains more than one character
*/