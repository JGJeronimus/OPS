/******************************************************************************
* File:         getsignal_sendpid.c                                           *
* Version:      1.0                                                           *
* Date:         2020-01-02                                                    *
* Author:       J.G. Jeronimus                                                * 
* Description:  OPS Assignment 7:					      *
*		Read input from stdin, convert lower-case characters to       *
*               upper case and write result to stdout.			      *
*               Use file descriptors and process one character at a 	      *		
*		time (read()/write()).					      *	
******************************************************************************/

#include <stdio.h>     // perror()
#include <stdlib.h>    // exit()
#include <unistd.h>    // read(),write(),close(), fork(), pipe(),dup2(), execl()
#include <sys/wait.h>  // wait()

#define ESC 0x1B

int main(void) {
  int pipeP2C[2];                            // write to filter
  int pipeC2P[2];                            // read from filter 
  pid_t pid_parent, pid_child, pid_received;               // process ID's
  int exitInt;                               

  // Create two unnamed pipes:
  if(pipe(pipeP2C) == -1) {
    perror("\n\tError: pipeP2C not available or has failed");
    exit(1);
  }
  if(pipe(pipeC2P) == -1) {
    perror("\n\tError: pipeC2P not available or has failed\n");
    exit(1);
  }
  
  switch(fork()) {
    
  case -1:
    perror("\n\tError: The fork has failed\n");
    exit(1);
    break;
    
  case 0:  // Child
    pid_child = getpid();
    printf("\n\t The PID of the child process is %d\n", pid_child);

    dup2(pipeP2C[0], 0);                    // Redirect stdin to pipeP2C: 
    close(pipeP2C[0]);                      // Close the unused input (read) of pipeP2C

    // Redirect stdout to pipeC2P:
    dup2(pipeC2P[1], 1);                    // Redirect stdin to the output (read) of pipeP2C
    close(pipeC2P[1]);                      // Close the unused output (write) of pipeC2P
    
    close(pipeC2P[0]);                      // Close pipeC2P input (read)
    
    // Call filter (and never return):
    execl("./filter", "filter", NULL);
    perror("\n\tError: The filter has failed:\n\n");
    exit(1);
    
    
  default:  // Parent
    pid_parent = getpid();
    printf("\n\tThe PID of the parent-process is %d\n", pid_parent);

    
    
    char getChar = 'o';
    char sendChar = 'o';

    sleep(1);
    printf("\n\tWrite the characters to be handled bij filter.c\n\n");
    read(0, &getChar, 1);                   // Read a character from stdin

    while (1) {
           
        if(getChar == ESC) {
          break;
        }

        write(pipeP2C[1],&getChar, 1);      // Write char to pipeP2C
        read(pipeC2P[0], &sendChar, 1);     // Read char from pipeC2P
        //printf("\n\tTHIS IS NOT FILTER\n"); // To prove that filter.c is not printing
        write(1, &sendChar, 1);             // Write char to stdout
        read(0, &getChar, 1);               // Read next char     
    }
        
    
    printf("\n\tInput 'Ctrl-[' or 'Escape' detected, child program will be terminated\n\n");
    close(pipeP2C[1]);                  // Output (write) of pipeP2C no longer needed
    printf("\n\tOutput of pipeP2C closed\n");
    close(pipeC2P[0]);                  // Input (read) of pipeC2P no longer needed
    printf("\n\tInput of pipeC2P closed\n\n");
    pid_child = getpid();               // pid_child might be used uninitialised
    kill(pid_child, SIGTERM);  
       
    pid_received = wait(&exitInt);
    printf("\n\tThe child with PID %d has exited with status 0x%x\n", pid_received, exitInt);
    
  }
  return 0;
}



/* geen magic numbers gebruiken, liever constant define ipv nummers voor gate