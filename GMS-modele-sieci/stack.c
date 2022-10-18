#include "stack.h"

#define MAXSIZE 100

vertex* stack[MAXSIZE];
int top = -1;

vertex* pop() 
{
    vertex* v;

    if (!empty()) 
    {
        v = stack[top];
        top--;
        return v;
    }
}

vertex* push(vertex* v) {

    if (!full()) 
    {
        top++;
        stack[top] = v;
    }
}

bool full() 
{
    return (top == MAXSIZE);
}

bool empty() 
{
    return (top == -1);
}