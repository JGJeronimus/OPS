//*****************************************************************************
* File:         main.c			                                                  *
* Version:      1.0                                                           *
* Date:         2019-12-27                                                    *
* Author:       J.G. Jeronimus                                                * 
* Description:  OPS exercise 8: Queues					                              *	
******************************************************************************/


#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  data_t data = {1, "Hello queue"};
  queue_t queue = {NULL};  // Note: element of queue = NULL
  
  printf("\nList the contents of the current queue:\n");
  showQueue(&queue);
  
  printf("\nCreate a new queue:\n");
  createQueue(&queue, data);
  showQueue(&queue);
  data.intVal++;
  
  
  
  printf("\nAdd new data to the queue:\n");
  pushQueue(&queue, data);
  showQueue(&queue);
  data.intVal++;
  
  printf("\nAdd new data to the queue:\n");
  pushQueue(&queue, data);
  showQueue(&queue);
  data.intVal++;
  
  printf("\nAdd new data to the queue:\n");
  pushQueue(&queue, data);
  showQueue(&queue);
  
  printf("\nRemove data from the queue:\n");
  popQueue(&queue);
  showQueue(&queue);
  
  
  
  printf("\nFront iValue/first node: %d\n", frontQueue(&queue)->intVal);
  printf("Back  iValue/last node:  %d\n", backQueue(&queue)->intVal);
  
  
  printf("\nDelete the current queue:\n");
  deleteQueue(&queue);
  showQueue(&queue);
  
  printf("\nCreate a new queue:\n");
  createQueue(&queue, data);
  showQueue(&queue);
  data.intVal++;
  
  return 0;
}
