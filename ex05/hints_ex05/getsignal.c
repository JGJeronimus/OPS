/******************************************************************************
* File:         getsignal.c
* Version:      1.2
* Date:         2017-11-20
* Authors:      M. van der Sluys, R.B.A. Elsinghorst, J.G. Rouland
* Description:  OPS exercise 6:  receive signals for synchronisation - use sigaction()
******************************************************************************/

#include <unistd.h>  // write(), pause(), sleep(), getpid()
#include <signal.h>  // sigaction(), struct sigaction, sigemptyset()
#include <stdio.h>   // printf()
#include <string.h>  // memset()

#define mySigNr 25

void mySigHandler(int signal);
char letter = '1';

int main(void) {
  struct sigaction act, oldact;
  
  printf("Waiting for signal %i.  My PID is %i.\n", mySigNr, getpid() );
  printf("In other words, issue   kill -%i %i   or   ./sendsignal %i   from a different terminal.\n", mySigNr, getpid(), getpid() );
  
  // Define SHR:
  memset(...);    // Fill act with NULLs by default
  act.sa_handler = ...;      // Set the custom SHR
  act.sa_flags = ...;                   // No flags
  sigemptyset(...);          // No signal masking during SHR execution 
  
  // Install SHR:
  ...
  
  
  // Not asked for in the exercise: wait for the first signal before starting loop:
  printf("Waiting for a first signal.\n");
  pause();       // Wait until a (handled) signal is delivered
  letter = '1';  // Was reset from 1 to 2 on first signal (in previous line)
  
  // Loop and print characters:
  while(1) {
    write(1, &letter, 1);
    sleep(1);
  }
  
  return 0;
}


// SHR:
void mySigHandler(int signal) {
  letter++;
  if(letter > '9') letter = '0';
}
