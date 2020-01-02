/******************************************************************************
* File:         getsignal_sendpid.c                                           *
* Version:      1.0                                                           *
* Date:         2019-12-24                                                    *
* Author:       J.G. Jeronimus                                                * 
* Description:  OPS exercise 6:  get signals for synchronisation -            * 
*                                no CL-argument, send PID over Pipe           *
******************************************************************************/

#include <unistd.h>     // write(), pause(), sleep(), getpid()
#include <signal.h>     // sigaction(), struct sigaction, sigemptyset()
#include <stdio.h>      // printf()
#include <string.h>     // memset()
#include <fcntl.h>      // open(), O_* constants
#include <sys/types.h>  // getPid()
#include <stdlib.h>     // strtoul(), exit()
#include <sys/stat.h>   // mkfifo()

#define _XOPEN_SOURCE 500 // for S_IFIFO in C99+

volatile sig_atomic_t signalCount = 0; // the counter that will count incomming signals
void mySigHandler(int signal);
// char letter = '1';             // startpoint for the 1 to 9 characters

int main(void) {
  struct sigaction act, oldact;  // for signal handling
  char message[21] = "00";       // Buffer 
  int fd = 0;                     
  int mySigNr = 25; 
  
  //int kill(__pid_t pid, int sig);
  
  pid_t pid = getpid();
  
  // Define SHR:
  memset(&act, '\0', sizeof(act));        // Fill act with NULLs by default
  act.sa_handler = mySigHandler;          // Set the custom SHR
  act.sa_flags = 0;                       // No flags
  sigemptyset(&act.sa_mask);              // No signal masking during SHR execution
  
  // Install SHR:
  sigaction(mySigNr, &act, &oldact);           // 25 ipv SIGINT

/* Open the FIFO */
  fd = open("PIDpipe", O_WRONLY);         // open de FIFO
    write(fd, &pid, sizeof(pid));         // Write the PID to the FIFO
    close(fd);

  
  printf("\n\tWaiting for signal %i.  My PID is %i.\n\n", mySigNr, getpid() );
  
  /*
  // Not asked for in the exercise: wait for the first signal before starting loop:
  printf("\n\tWaiting for a first signal.\n\n");
  pause();                                // Wait until a (handled) signal is delivered
  letter = '1';                           // Was reset from 1 to 2 on first signal (in previous line)
  
  // Loop and print characters:
  while(1) {
    sleep(3);
    //snprintf(message, sizeof(message));
    write(2, &message, 2);
    write(2, "\n", 1);
   */ 
  while(1){
        sleep(1); // creates a delay for the while loop
        snprintf(message, sizeof(message), "%d",signalCount); // print int 'signalCount' into the char[] result
        write(2, &message , 2); // writes result to the screen unbuffered.  

  }
  return 0;
}

void mySigHandler(int signal) {
  signalCount++;
  printf("\t %d \n", signalCount);        // TESTING PUPOSE ONLY

  if(signalCount > 9) {
    signalCount = 0;                      // reset letter to '0' if greater then '9'
    printf("\n\tsignalCount reset!\n\n");     // TESTING PURPOSE ONLY 
  }
  /* 
// SHR:
void mySigHandler(int signal) {
  letter++;
  printf("\n\t+1\n");                     // TESTING PUPOSE ONLY

  if(letter > '9') {
    letter = '0';                         // reset letter to '0' if greater then '9'
    printf("\n\tletter reset!\n");        // TESTING PURPOSE ONLY 
  } */
}


/*  Answer to questions
    Question: What happens when you send signal number 9 instead of 25?
    The process got killed instantly, see bashline command <kill -l>

*/  

