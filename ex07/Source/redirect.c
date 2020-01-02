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
  int pipeP2C[2], pipeC2P[2];
  char letter;
  
  // Create two unnamed pipes:
  if(pipe(pipeP2C) == -1) {
    perror("pipeP2C");
    exit(1);
  }
  if(pipe(pipeC2P) == -1) {
    perror("pipeC2P");
    exit(1);
  }
  
  switch(fork()) {
    
  case -1:
    perror("fork");
    exit(1);
    break;
    
  case 0:  // Child
    // Redirect stdin to pipeP2C:
    ...;  // Close stdin of child (filter) and redirect it to the output (read) of pipeP2C
    ...;  // Close pipeP2C input (read)
    ...;  // Close pipeP2C output (write)
    
    // Redirect stdout to pipeC2P:
    ...;  // Close stdout of child (filter) and redirect it to the input (write) of pipeC2P
    ...;  // Close pipeC2P input (read)
    ...;  // Close pipeC2P output (write)
    
    // Call filter (and never return):
    execl("./filter", "filter", (char*)NULL );
    perror("filter");
    exit(1);
    break;
    
  default:  // Parent
    ...;  // Close the unused input (read) of pipeP2C
    ...;  // Close the unused output (write) of pipeC2P
    
    read(0, &letter, 1);  // Read a character from stdin
    
    while(letter != ESC) {
      ...;   // Write char to pipeP2C
      ...;   // Read char from pipeC2P
      ...;   // Write char to stdout
      ...;   // Read next char
    }
    
    ...;  // Output (write) of pipeP2C no longer needed
    ...;  // Input (read) of pipeC2P no longer needed
    
    wait(NULL);
    break;
  }
  return 0;
}

