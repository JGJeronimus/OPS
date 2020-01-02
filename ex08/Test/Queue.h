
 //*****************************************************************************
 * File:         Queue.h			                                                 *
 * Version:      1.0                                                           *
 * Date:         2020-01-02                                                    *
 * Author:       J.G. Jeronimus                                                * 
 * Description:  OPS Assignment 8: Queues				                               *
 ******************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

#define TEXT_SIZE 20

// This struct may not contain pointers pointing outside the struct
typedef struct {
  int intVal;
  char text[TEXT_SIZE];
} data_t;

typedef struct node {
  data_t data;
  struct node* nextNode;
} node_t;

// Implementation: circular linearly linked list
typedef struct {
  node_t* lastNode;
} queue_t;

void createQueue(queue_t* queue, data_t data);
int emptyQueue(const queue_t* queue);
size_t sizeQueue(const queue_t* queue);
data_t* frontQueue(const queue_t* queue);
data_t* backQueue(const queue_t* queue);
void pushQueue(queue_t* queue, data_t data);
void popQueue(queue_t* queue);
void deleteQueue(queue_t* queue);
void showQueue(const queue_t* queue);

#endif
