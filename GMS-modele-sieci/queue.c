#include "stack.h"



//memset(Q, 0, QSIZE * sizeof(*visited));


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

int frontQ()
{
    return head;
}

bool emptyQ()
{
    return (head == tail);
}