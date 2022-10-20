#ifndef STACK_H
#define STACK_H

#include "functions.h"

typedef struct _vertex vertex;


typedef struct _snode
{
	vertex* v;
	struct _snode* ptr;
}snode;

typedef struct _stack
{
	snode* top;
	snode* bottom;
	int counter;
}stack;

stack* createStack();
void push(stack* s, vertex* v);
vertex* pop(stack* s);
vertex* top(stack* s);
bool empty(stack* s);


#endif // !STACK_H