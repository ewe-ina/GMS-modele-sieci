#include "stack.h"

stack* createStack()
{
    stack* s = (stack*)malloc(sizeof(stack));
    if (s == NULL)
        return NULL;
    s->top = NULL;
    s->bottom = NULL;
    s->counter = 0;

    return s;
}

void push(stack* s, vertex* v)
{
    snode* node = (snode*)malloc(sizeof(snode));
    if (node != NULL)
    {
        node->v = v;
        node->ptr = NULL;

        if (s->counter == 0) //dodaj pierwszy wierzcho³ek na stos
        {
            s->bottom = node;
            
        }
        else // dodaj na wierzchu stosu nowy bêdzie wskazywa³ na top
        {
            node->ptr = s->top;
        }
        s->counter++;
        s->top = node; // przesuwamy wska¿nik do góry
    }
}

vertex* pop(stack* s)
{
    if (s->bottom == NULL)
    {
        return NULL;
    }

    snode* temp = s->top;
    vertex* v = temp->v;
    s->top = s->top->ptr; //przesuwamy wskaŸni top o jeden nizej
    if (s->top == NULL) // to by³ ostatni na nic ni¿ej nie wskazal
    {
        s->bottom = NULL;
    }
    free(temp);
    temp = NULL;
    s->counter--;
    return v;
}

vertex* top(stack* s) 
{
    if (s->top == NULL)
    {
        return NULL;
    }
    return s->top->v;
}

bool empty(stack* s)
{
    return s->counter == 0;
}
