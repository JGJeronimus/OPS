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

//#define mySigNr 25

//unsigned int seconds = 3;
//unsigned int sleep(unsigned int seconds);

int main(int argc, char *argv[]) {
  unsigned long int endpoint;
  if(argc != 2) {
    write(2, "Please give the PID of the receiving process as an argument.\n", 62);
    // exit(1);
  }
  else
    {
    endpoint = strtoul(argv[1], NULL, 10);
    while(1) {
      sleep(3);
      kill(endpoint, 25);
      }
    }  
  
 // Get PID from command line:
 // pid_t PID = (pid_t) strtoul(argv[1], NULL, 10);
  
  // Send a signal every 3 seconds:
  
    
  
  
  return 0;
}
