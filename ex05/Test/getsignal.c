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
unsigned int seconds = 1;
unsigned int sleep(unsigned int seconds);
int kill(__pid_t pid, int sig);
int sig;

int main(void) {
  struct sigaction act, oldact;
  
  printf("Waiting for signal %i.  My PID is %i.\n", mySigNr, getpid() );
  printf("In other words, issue   kill -%i %i   or   ./sendsignal %i   \nfrom a different terminal.\n", mySigNr, getpid(), getpid() );
  
  // Define SHR:
  memset(&act, '\0', sizeof(act));        // Fill act with NULLs by default
  act.sa_handler = mySigHandler;          // Set the custom SHR
  act.sa_flags = 0;                       // No flags
  sigemptyset(&act.sa_mask);              // No signal masking during SHR execution
  
  // Install SHR:
  sigaction(SIGINT, &act, &oldact);

  
  
  // Not asked for in the exercise: wait for the first signal before starting loop:
  printf("\nWaiting for a first signal.\n");
  pause();                                // Wait until a (handled) signal is delivered
  letter = '1';                           // Was reset from 1 to 2 on first signal (in previous line)
  
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


/*  Answer to questions
    Question: What happens when you send signal number 9 instead of 25?
    The process got killed instantly
*/  

