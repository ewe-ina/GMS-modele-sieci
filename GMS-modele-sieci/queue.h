// kolejka intów do BFS
#ifndef QUEUE_H
#define QUEUE_H

#include "functions.h"

typedef struct _qnode
{
	int data;
	struct _qnode* next;
}qnode;

typedef struct _queue
{
	qnode *head;
	qnode* tail;
	int couter;
}queue;

queue* createQueue();
void enqueue(queue *q, int data);
int dequeue(queue *q);
int frontQ(queue* q);
bool emptyQ(queue *q);

#endif // !QUEUE_H
