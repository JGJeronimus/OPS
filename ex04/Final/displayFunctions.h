/******************************************************************************
 * File:         displayFunctions.h
 * Version:      1.4
 * Date:         2018-02-20
 * Author:       M. van der Sluys, J.H.L. Onokiewicz, R.B.A. Elsinghorst, J.G. Rouland
 * Description:  OPS exercise 2: Declarations for displayFunctions.c
 ******************************************************************************/

#ifndef displayFunctionsH
#define displayFunctionsH

#include "errorCodes.h"

ErrCode SyntaxCheck(int argc, char **argv);
/*
  Input:    argc = number of command-line parameters to test
            argv = begin adress of array of pointers
                          to command-line parameters
  Precondition:	none
  Function: Check whether:
            - argc = 5
            - second parameter is 'e', 'p' or 'w'
            - third parameter = positive integer
            - fourth parameter = integer
            - firft and further = one single character
  Postcondition:	none
  Output:   Error code:
            0 = NO_ERR:         No error
            1 = ERR_PARS:	Number of command-line parameters is not equal to 5
            2 = ERR_TYPE:	Unknown print method
            3 = ERR_NR:		Number of times is no positive integer
            4 = ERR_NICE: Nice Increment is not an integer
            5 = ERR_CHAR:	Print text contains more than one character
*/

void DisplayError(ErrCode errCode);
/*
  Input:	errCode = Error code
  Precondition:	None
  Function: Depending on the error code, an error message is printed to screen:
            errCode = 0: No error message
            errCode = 1: Number of command-line parameters is not equal to 5
            errCode = 2: Unknown print method
            errCode = 3: Number of times is no positive integer
            errCode = 4: Nice Increment is not an integer
            errCode = 5: Print text contains less then one character
            errCode > 5: Non-existing error message
  Postcondition:	Error message is on the display
  Output:		None
*/

void PrintCharacters(char prType, unsigned long numberOfTimes, int niceIncr, char prChar);
/*
  Input:    prType = printing method:
            'e' = echo
            'p' = printf
            'w' = write
            numberOfTimes = number of times the character should be printed
            niceIncr = the amount which the nice-value should be altered
            prChar = character to print
  Precondition:	  input parameters should be correct
  Function:	      prChar shall be printed to display numberOfTimes times
  Postcondition:  prChar shall is on the display numberOfTimes times
  Output:	  None
*/

#endif
