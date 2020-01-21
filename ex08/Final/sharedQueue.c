/******************************************************************************
* File:         sharedQueue                                                   *
* Version:      1.1                                                           *
* Date:         2020-01-18                                                    *
* Author:       J.G. Jeronimus                                                *
* Description:  OPS Assignment 8:			                                  *
*	              Multithreading, a shared queue, mutexes and Valgrind        *
******************************************************************************/


#include "Queue.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#define _POSIX_C_SOURCE 199309L

void* Producer(void *arg);
void* Consumer(void *arg);
void controlC_fix();
int threadRunning = 1;

struct arg_struct {
    char character;
    int time;
    queue_t *queue;
    data_t *data;
    pthread_mutex_t *mutex;
    int *threadRunning;
}args;

data_t data = {1, "O"};
queue_t queue = {NULL};  // Note: element of queue = NULL

 

int main() {
  
  printf("\n\t Program started!\n\n");

  struct sigaction act, oldact;

  /* Define the SHR */
  memset(&act, '\0', sizeof(act));                                  // fills act with null's by default.
  act.sa_handler = controlC_fix;                                    // set the custom SHR.
  act.sa_flags = 0;                                                 // define the flags used.
  sigemptyset(&act.sa_mask);                                        // define the signal masking
  
  /* Install the SHR */
  sigaction(SIGINT, &act, &oldact);                                 // This cannot be SIGKILL of SIGSTOP
  
  pthread_t producer_1, producer_2, producer_3, consumer_1;
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

  


  //initialize and configure the thread data
  struct arg_struct thread1;
  struct arg_struct thread2;
  struct arg_struct thread3;
  struct arg_struct thread4;

  thread1.character = '1';
  thread2.character = '2';
  thread3.character = '3';

  // Install the mutex's  
  thread1.mutex = &mutex;
  thread2.mutex = &mutex;
  thread3.mutex = &mutex;
  thread4.mutex = &mutex;
  
  // Install the timers for the threads
  thread1.time = 2;
  thread2.time = 3;
  thread3.time = 4;
  thread4.time = 15;

  thread1.queue = &queue;
  thread2.queue = &queue;
  thread3.queue = &queue;
  thread4.queue = &queue;

  thread1.data = &data;
  thread2.data = &data;
  thread3.data = &data;
  thread4.data = &data;

  thread1.threadRunning = &threadRunning;
  thread2.threadRunning = &threadRunning;
  thread3.threadRunning = &threadRunning;
  thread4.threadRunning = &threadRunning;

  // Create the threads and let them join in the end.
  pthread_create(&producer_1, NULL, Producer, &thread1);
  pthread_create(&producer_2, NULL, Producer, &thread2);
  pthread_create(&producer_3, NULL, Producer, &thread3);
  pthread_create(&consumer_1, NULL, Consumer, &thread4);

  pthread_join(producer_1, NULL);
  pthread_join(producer_2, NULL);
  pthread_join(producer_3, NULL);
  pthread_join(consumer_1, NULL);
 
  printf("\n\tProgram finished.\n");

  return 0;
}

// Start the producer threat and print a character to the queue ever 2, 3 or 4 seconds
void* Producer(void *arg) {
    struct arg_struct *args = (struct arg_struct *)arg;
    printf("\tthreadRunning = %d\n", *args -> threadRunning);
    while(*args -> threadRunning == 1) {
        sleep(args -> time);
        pthread_mutex_lock(args -> mutex);
        *args -> data -> text = args -> character;
        if(sizeQueue(args -> queue) < 1){
            printf("\tcreate a new queue\n");
            createQueue(args -> queue, *args -> data);
            args -> data -> intVal++;
        } else {
            printf("\tcreate a new node\n");
            pushQueue(args -> queue, *args -> data);
            args -> data -> intVal++;
        }
        pthread_mutex_unlock(args -> mutex); 
    };
    return NULL;
}

// Start the consumer-thread and write the data to chracter_log.txt and empty the queue every 15 seconds.
void* Consumer(void *arg) {
    struct arg_struct *args = (struct arg_struct *)arg;
    node_t* currentNode;
    int queueLength = 0;
    int i;
    int nodesCreated = 0;
    
    while(*args -> threadRunning == 1) {
        printf("\n\tconsumer started!\n\n");
        sleep(args -> time);
        pthread_mutex_lock(args -> mutex);
        for(currentNode = args -> queue -> lastNode; currentNode != NULL && currentNode->nextNode != args->queue->lastNode; currentNode = currentNode->nextNode){
            FILE * fPtr;
            fPtr = fopen("character_log.txt", "a");
            //printf("\tappend to file executed\n");
            //printf("\tdata.text = %s\n", currentNode -> data.text);
            fputs(currentNode -> data.text, fPtr);
            fclose(fPtr);
        }
        // print the queue to the screen.
        showQueue(args -> queue);
        nodesCreated = 0;
        queueLength = sizeQueue(args -> queue);
        printf("\tThe lenght of the queue was %d\n", queueLength);
        for(i = 0; i < queueLength; i++) {
            popQueue(args -> queue);
            nodesCreated++;
        }
        printf("\tThere where %d nodes created\n", nodesCreated);
        showQueue(args -> queue);
        pthread_mutex_unlock(args -> mutex); 
    };
        return NULL;
}

void controlC_fix() {
  threadRunning = 0;
};