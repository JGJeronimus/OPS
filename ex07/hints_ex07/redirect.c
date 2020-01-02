/******************************************************************************
 * File:         redirect.c
 * Version:      1.3
 * Date:         2012-02-04, 2016-04-28, 2017-12-12, 2018-04-25
 * Author:       M. van der Sluys, R.B.A. Elsinghorst, J.G. Rouland
 * Description:  Input text through stdin, send to child proces filter through unnamed
 *               pipe, receive result through unnamed pipe and write to stdout.
 *               Processes text one character at a time (read()/write()).
 ******************************************************************************/

#include <stdio.h>     // perror()
#include <stdlib.h>    // exit()
#include <unistd.h>    // read(),write(),close(), fork(), pipe(),dup2(), execl()
#include <sys/wait.h>  // wait()

#define ESC 0x1B

int main(void) {
  int pipeP2C[2];                            // write to filter
  int pipeC2P[2];                            // read from filter 
  pid_t pid_parent, pid_child, pid_received; // process ID's
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
    close(0);                               // Close stdin of child (filter)
    //close(pipeP2C[0]);                      // Close stdin of child (filter) 
    //dup2(pipeP2C[1], 0);                    // Redirect stdin to the output (read) of pipeP2C

    close(pipeP2C[0]);                      // Close pipeP2C input (read)
    close(pipeP2C[1]);                      // Close pipeP2C output (write)
    
    // Redirect stdout to pipeC2P:
    close(1);                  // Close stdout of child (filter) and redirect it to the input (write) of pipeC2P
    close(pipeC2P[0]);         // Close pipeC2P input (read)
    close(pipeC2P[1]);         // Close pipeC2P output (write)
    
    // Call filter (and never return):
    execl("./filter", "filter", (char*)NULL );
    perror("\n\tError: The filter has failed\n");
    exit(1);
    
    
  default:  // Parent
    pid_parent = getpid();
    printf("\n\tThe PID of the parent-process is %d\n", pid_parent);

    close(pipeP2C[0]);                  // Close the unused input (read) of pipeP2C
    close(pipeC2P[1]);                  // Close the unused output (write) of pipeC2P
    
    char getChar = 'o';
    char sendChar = 'o';


    read(0, &getChar, 1);               // Read a character from stdin
           
        if(getChar != ESC) {
          write(pipeP2C[1],&getChar, 1);    // Write char to pipeP2C
          read(pipeC2P[0], &sendChar, 1);   // Read char from pipeC2P
          write(1, &sendChar, 1);           // Write char to stdout
          read(0, &getChar, 1);             // Read next char
        }

        else {
          printf("\n\tInput 'Ctrl-[' or 'Escape' detected, child program will be terminated\n\n");
          kill(pid_child, SIGTERM);
          break;
        }
      
      
    
    close(pipeP2C[1]);                  // Output (write) of pipeP2C no longer needed
    close(pipeC2P[0]);                  // Input (read) of pipeC2P no longer needed
    //kill(pid_child, SIGTERM);
    wait(NULL);
    
    pid_received = wait(&exitInt);
    printf("\n\tThe child with PID %d has exited with status 0x%x\n", pid_received, exitInt);
  }
  return 0;
}

