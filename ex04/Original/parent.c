/******************************************************************************
 * File:         display.c
 * Version:      1.4
 * Date:         2018-02-20
 * Author:       M. van der Sluys, J.H.L. Onokiewicz, R.B.A. Elsinghorst, J.G. Rouland
 * Description:  OPS exercise 2: syntax check
 ******************************************************************************/

#include <stdio.h>                // printf(), file IO, perror()
#include <stdlib.h>               // exit()
#include <sys/wait.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>            // getpid()
#include "displayFunctions.h"

int main(int argc, char *argv[]) {
  unsigned long int numOfTimes;
  char printMethod; 
  //char printChar;                           // unused for now.
  int niceIncr = 0;                           // number to calculate the nicefactor
  int numChild = 0;                           // fork counter
  int iChild = 0;                             // number of childs
  pid_t pids[25] ={0};                        // signed integer!
  ErrCode err;
  
  err = SyntaxCheck(argc, argv);              // Check the command-line parameters
  if(err != NO_ERR) {
    DisplayError(err);                        // Print an error message
  } else {
    printMethod = argv[1][0];
    numOfTimes = strtoul(argv[2], NULL, 10);  // String to unsigned long
    niceIncr = atoi(argv[3]);
    //printChar = argv[4][0];                 // unused for now
    
    printf("The printMethod = %c\n", printMethod);
    printf("The number of Times = %lu\n", numOfTimes);
    printf("The increment of Nice = %d\n", niceIncr);
    int numChar = 0;
    for(numChar =4; numChar < argc; numChar++){
      printf("The received argument is character %s \n", argv[numChar]); // 3C
      numChild++;
      }

    printf("\nnumber of forks to be made is %d\n\n", numChild);

    for (iChild = 1; iChild <= numChild; iChild++){

      if((pids[iChild] = fork()) <0){           // assignment 3C
        perror("fork failed\n");
        exit(-1);
        }
      
      else if (pids[iChild] == 0){
          nice(iChild * niceIncr);
          printf("iChild = %d with pid: %d and the nicefactor for this child is %d \n", iChild, getpid(), getpriority(PRIO_PROCESS, 0));
          PrintCharacters(printMethod, numOfTimes, argv[iChild + 3][0]);
          exit(0);
          }
      
      }
      int status =0;
      pid_t pid;

      while (numChild > 0){
        numChild --;
        pid = wait(&status);
        printf("\n\nThe child with id %d and status 0x%x is killed\n\n", pid, status);
      }
      
      
      

       
  }
  
  printf("\n");  // Newline at end
  return 0;
}
