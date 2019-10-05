/******************************************************************************
 * File:           syntaxCheck.h
 * Version:        1.1
 * Date:           2016-03-18
 * Author:         M. van der Sluys, R.B.A. Elsinghorst, J.G. Rouland
 * Description:    OPS exercise 4: declaration of the functions SyntaxCheck() and
 *                 DisplayError()
 ******************************************************************************/

#ifndef syntaxCheckH
#define syntaxCheckH

#include "errorCodes.h"

ErrCode SyntaxCheck(int argc, char **argv);
/*
  Input:    argc = number of command-line parameters to test
            argv = begin adress of array of pointers
                          to command-line parameters
  Precondition:	none
  Function: Check whether:
            - argc == 7
            - nice increment is positive integer
  Postcondition:	none
  Output:   Error code:
            0 = NO_ERR:    No error
            2 = ERR_PARS:  Number of command-line parameters is not >4
            5 = ERR_NICE:  Nice increment is no positive integer
*/

void DisplayError(ErrCode errCode);
/*
  Input:         errCode = Error code
  Precondition:	 None
  Function: Depending on the error code, an error message is printed to screen:
            errCode = 0:  No error message
            errCode = 1:  Number of command-line parameters does not exceed 4
            errCode = 5:  Nice increment is no positive integer
            errCode > 5:  Non-existing error message
  Postcondition:	Error message is displayed
  Output:		None
*/

#endif
