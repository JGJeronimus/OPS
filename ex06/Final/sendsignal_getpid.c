/******************************************************************************
* File:         sendsignal_getpid.c                                           *
* Version:      1.0                                                           *
* Date:         2019-12-24                                                    *
* Author:       J.G. Jeronimus                                                * 
* Description:  OPS exercise 6:  send signals for synchronisation -           * 
*                                no CL-argument checking, get PID over Pipe   *
******************************************************************************/

#include <stdlib.h>       // strtoul(), exit()
#include <unistd.h>       // sleep(), read(), write(), close()
#include <signal.h>       // kill()
#include <stdio.h>        // printf(), perror()
#include <sys/stat.h>     // mkfifo()
#include <fcntl.h>        // open(), O_* constants
#include <sys/types.h>    // getPid()
#define _XOPEN_SOURCE 500 // for S_IFIFO in C99+

//int main(int argc, char *argv[]) {
int main(void) {
    int pid = 0;
    unsigned long int endpoint;
    int fd =0;
    int mySigNr = 25;

    printf("\n\tModule started succesfull, opening FIFO\n");
    fd = open("PIDpipe", O_RDONLY);                                          // Open the FIFO read-only
    printf("\n\tFIFO opened succesfull, start reading PID\n");
    
    read(fd, &pid, sizeof(pid));                                             // Optain PID from FIFO

    printf("\n\tPID %d received\n", pid);
    close(fd);                                                               // close FIFO
    printf("\n\tFIFO closed, endpoint set to PID of getsignal_sendpid.c\n");
    
    endpoint = pid;                                                          // endpoint set

    while(1) {
      sleep(25);                                                              // Send a signal every 3 seconds:
      kill(endpoint, mySigNr);
      //printf("\n\tkill-command send\n"); 
      }
}
