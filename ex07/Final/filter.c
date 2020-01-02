/******************************************************************************
* File:         getsignal_sendpid.c                                           *
* Version:      1.0                                                           *
* Date:         2019-12-27                                                    *
* Author:       J.G. Jeronimus                                                * 
* Description:  OPS Assignment 7:					      *
*		Read input from stdin, convert lower-case characters to       *
*               upper case and write result to stdout.			      *
*               Use file descriptors and process one character at a 	      *		
*		time (read()/write()).					      *	
******************************************************************************/

#include <unistd.h>  // read(), write()
#include <ctype.h>   // toupper()
#include <stdio.h>   // printf()

#define ESC 0x1B

int main(void) {
  char letter;
  
  read(0, &letter, 1);          // read first char from stdin
  
  while(letter != ESC) {        // ESC = Ctrl-[ in shell
    printf("\n\tTHIS IS FILTER");
    letter = toupper(letter);   // convert to lower case
    write(1, &letter, 1);       // write char to stdout
    read(0, &letter, 1);        // read next char from stdin
  }
  return 0;
}
