/******************************************************************************
* File:         sendsignal.c
* Version:      1.1
* Date:         2017-11-20
* Authors:      M. van der Sluys, R.B.A. Elsinghorst, J.G. Rouland
* Description:  OPS exercise 6:  send signals for synchronisation - only basic CL-argument checking!
******************************************************************************/

#include <stdlib.h>  // strtoul(), exit()
#include <unistd.h>  // sleep()
#include <signal.h>  // kill()
#include <stdio.h>   // printf()

#define mySigNr ...

int main(int argc, char *argv[]) {
  if(argc != 2) {
    printf("Please give the PID of the receiving process as an argument.\n");
    exit(1);
  }
  
  // Get PID from command line:
  pid_t PID = (pid_t) strtoul(argv[1], NULL, 10);
  
  // Send a signal every 3 seconds:
  while(1) {
    ...
    sleep(...);
  }
  
  return 0;
}
