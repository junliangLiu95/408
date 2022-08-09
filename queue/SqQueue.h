#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 10
#define STACKINCREMENT 5
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define MAXQSIZE 5

typedef int Status;

typedef int ElemType;

typedef struct
{
    ElemType *base;
    int front;
    int rear;
} SqQueue;

/*
         empty queue       insert 1    insert 2     pop queue    full queue    full queue
               [*]             [*]           [*]          [*]    rear [*]         [3]
               [*]             [*]           [*]          [*]         [4]         [2]
               [*]             [*]      rear [*]     rear [*]         [3]   front [1]
               [*]        rear [*]           [2]    front [2]         [2]    rear [*]
  front & rear [*]       front [1]     front [1]          [*]   front [1]         [4]
*/

Status InitQueue(SqQueue *Q)
{
    Q->base = (ElemType *)malloc(sizeof(ElemType));
    if (!Q->base)
        exit(OVERFLOW);
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

int QueueLength(SqQueue Q)
{
    return (Q.rear + MAXQSIZE - Q.front) % MAXQSIZE;
}

Status EnQueue(SqQueue *Q, ElemType e)
{
    if ((Q->rear + 1) % MAXQSIZE == Q->front)
        return OVERFLOW;
    Q->base[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAXQSIZE;
    return OK;
}

Status DeQueue(SqQueue *Q, ElemType *e)
{
    if (Q->front == Q->rear)
    {
        return OVERFLOW;
    }
    *e = Q->base[Q->front];
    Q->front = (Q->front + 1) % MAXQSIZE;
    return OK;
}

void QueueTraverse(SqQueue Q)
{
    int index = Q.front;
    while (index != Q.rear)
    {
        printf("%d ", Q.base[index]);
        index = (index + 1) % MAXQSIZE;
    }
    printf("\n");
}