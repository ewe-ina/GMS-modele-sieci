//#include "stack.h"
//
//
//
//queue *createQueue()
//{
//    queue* q = (queue*)malloc(sizeof(queue));
//    if (q == NULL)
//        return NULL;
//    q->head = NULL;
//    q->tail = NULL;
//    q->counter = 0;
//
//    return q;
//}
//
//void enqueue(queue* q, int data)
//{
//    qnode* node = (qnode*)malloc(sizeof(qnode));
//    if (node != NULL)
//    {
//        node->data = data;
//        node->next = NULL;
//        
//        if (q->head == NULL) // dodaj pierwszy element
//        {
//            q->head = node;
//        }
//        else  // dodaj na koñcu kolejki
//        {
//            q->tail->next = node;
//        }
//        q->counter++;
//        q->tail = node; // przesuñ wskaŸnik na nowy ogon
//    }
//}
//
//int dequeue(queue* q)
//{
//    if (q->head == NULL)
//    {
//        return -1;
//    }
//
//    qnode* temp = q->head;
//    int data = temp->data;
//    q->head = q->head->next;
//    if (q->head == NULL)    // jeœli usunêliœmy ostatniego noda
//    {
//        q->tail = NULL;
//    }
//    free(temp);
//    temp = NULL;
//    q->counter--;
//    return data;
//}
//
//int frontQ(queue* q)
//{
//    if (q->head == NULL)
//    {
//        return -1;
//    }   
//    return q->head->data;
//}
//
//bool emptyQ(queue* q)
//{
//    return q->counter == 0;
//}
