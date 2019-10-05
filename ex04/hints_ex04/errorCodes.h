/************************************************************
 * File:         errorCodes.h
 * Version:      1.1
 * Date:         2016-03-18
 * Author:       M. van der Sluys, R.B.A. Elsinghorst, J.G. Rouland
 * Description:  Definition of the type ErrCode containing error
 *               codes used for OPS exercise 4.
 ************************************************************/

#ifndef errorCodesH
#define errorCodesH

#define NUM_OF_PARS 7
/* Number of required parameters on the command line,
   including the program name */

typedef enum {NO_ERR, ERR_PARS, ERR_TYPE, ERR_NR, ERR_CHAR, ERR_NICE} ErrCode;
/*
  NO_ERR    No syntax error occurred in the command line
  ERR_PARS  The number of command-line parameters is less than 5
  ERR_TYPE  The print type is incorrect (not one of 'e', 'p' or 'w')
  ERR_NR    The number is not a positive integer
  ERR_CHARS The print text contains more than one character
  ERR_NICE  The nice increment is not an integer
*/

#endif
