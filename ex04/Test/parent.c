/******************************************************************************
 * File:         display.c
 * Version:      1.4
 * Date:         2018-02-20
 * Author:       M. van der Sluys, J.H.L. Onokiewicz, R.B.A. Elsinghorst, J.G. Rouland
 * Description:  OPS exercise 2: syntax check
 ******************************************************************************/

#include <stdio.h>                // printf(), file IO, perror()
#include <stdlib.h>               // exit()
#include <sys/wait.h>             // wait()
#include <unistd.h>               // execl()
#include <sys/time.h>             // setpriority()
#include <sys/resource.h>         // getpriority()
#include <sys/types.h>            // getpid()
#include "displayFunctions.h"

int main(int argc, char *argv[]) {
  unsigned long int numOfTimes;
  char printMethod; 
  int niceIncr = 0;                           // number to calculate the nicefactor
  int numChild = 0;                           // fork counter
  int iChild = 0;                             // number of childs
  int numChar = 0;
  pid_t pids[25] ={0};                        // signed integer!
  
  
  ErrCode err;
  
  err = SyntaxCheck(argc, argv);              // Check the command-line parameters
  if(err != NO_ERR) {
    DisplayError(err);                        // Print an error message
    } 
    else {
      printMethod = argv[1][0];
      numOfTimes = strtoul(argv[2], NULL, 10);  // String to unsigned long <stdlib>
      niceIncr = atoi(argv[3]);
      printf("\n\t...SyntaxCheck OK, launching program...\n");
      printf("\n\tThe printMethod =     %c\n", printMethod);
      printf("\tThe number of Times = %lu\n", numOfTimes);
      printf("\tThe Nice-Increment =  %d\n\n", niceIncr);
    
    for(numChar =4; numChar < argc; numChar++){
        printf("\tThe the number %i character received is %s \n",(numChild +1), argv[numChar]); // 3C
        numChild++;
    }
    /* Todo: make message on line 43 better with 1st, 2nd, 3th etc. (if statement?) */

    printf("\n\tnumber of forks to be made is %d\n\n", numChild);
    
    for (iChild = 1; iChild <= numChild; iChild++){

      if((pids[iChild] = fork()) <0){           
        perror("fork failed\n");
        exit(-1);
        }
      
      else if (pids[iChild] == 0){
          nice(iChild * niceIncr);
          execl("/home/student/Desktop/exercises/OPS/ex02/Final/display", "display", argv[1], argv[2], argv[iChild +3], NULL);
          printf("\tiChild = %d with pid: %d and the nicefactor for this child is %d \n\n", iChild, getpid(), getpriority(PRIO_PROCESS, 0));
          perror("\n\tError, failed to execute child with execl()\n");
          //PrintCharacters(printMethod, numOfTimes, niceIncr, argv[iChild + 3][0]);
          exit(0);
          }
      
      }
      int status =0;
      pid_t pid;

      while (numChild > 0){
        numChild --;
        pid = wait(&status);
        printf("\n\n\tThe child with id %d and status 0x%x is killed\n\n", pid, status);
      }
      
      if (numChild == 0){
        printf("\n\tSucces! All children have finished their tasks! \n\n");
        exit(0);
      }
      
      

       
  }
    
  printf("\n");  // Newline at end
  return 0;
}
