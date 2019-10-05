/******************************************************************************
 * File:         sendsiggetpid.c
 * Version:      1.2
 * Date:         2017-12-04
 * Authors:      M. van der Sluys, R.B.A. Elsinghorst, J.G. Rouland
 * Description:  Receive PID through FIFO IDpipe and send signals 
 *               for synchronisation.  Note: IDpipe must exist (mkfifo IDpipe)!
 ******************************************************************************/

#include <stdlib.h>    // exit()
#include <stdio.h>     // printf()
#include <unistd.h>    // read(), close(), sleep()
#include <signal.h>    // kill()
#include <fcntl.h>     // open(), O_RDONLY

#define mySigNr 25

int main(void) {
  pid_t pid;
  int fd;
  
  // Get PID from FIFO:
  // ... open FIFO
  if(fd < 0) {
    printf("Opening IDpipe failed - did you create it?\n");
    exit(1);
  }
  // ...  read PID from FIFO
  // ...  close FIFO
  
  // Send a signal every three seconds:
  while(1) {
    // ... send the signal mySigNr to PID
    // ... sleep for three seconds
  }
  
  return 0;
}
