/******************************************************************************
 * File:         getsigsendpid.c
 * Version:      1.2
 * Date:         2017-12-04
 * Authors:      M. van der Sluys, R.B.A. Elsinghorst, J.G. Rouland
 * Description:  Receive signals for synchronisation and send PID
 *               through FIFO IDpipe.  Note: IDpipe must exist (mkfifo IDpipe)!
 ******************************************************************************/

#include <unistd.h>  // write(), sleep(), getpid(), close()
#include <signal.h>  // sigaction(), sigemptyset(), struct sigaction
#include <stdio.h>   // printf()
#include <stdlib.h>  // exit()
#include <fcntl.h>   // open(), O_WRONLY
#include <string.h>  // memset()

#define mySigNr 25

char letter = 'Z';

void mySigHandler(int signal);

int main(void) {
  // ...
  int fd;
  pid_t pid = getpid();
  
  // Define SHR:
  // ...
  
  // Install SHR:
  // ...
  
  // Send PID through FIFO:
  fd = // ... open FIFO named IDpipe, write-only
  if(fd < 0) {
    printf("Opening IDpipe failed - did you create it?\n");
    exit(1);
  }
  write( // ... write PID to FIFO
  // ... close FIFO
  
  // Write a letter to the screen every second:
  while(1) {
    write(1, &letter, 1);
    sleep(1);
  }
  
  return 0;
}

void mySigHandler(int signal) {
  letter++;
  if(letter > 'Z') {
    letter = 'A';
  }
}
