#include "stack.h"

#define QSIZE 200

int Q[QSIZE];
int head;
int tail;

void enqueue(int v)
{
    Q[tail] = v;
    if (tail == QSIZE - 1)
        tail = 1;
    else
        tail++;
}

int dequeue()
{
    int v = Q[head];
    if (head == QSIZE - 1)
        head = 0;
    else
        head++;
    return v;
}

bool emptyQ()
{
    return (head == tail);
}