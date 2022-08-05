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

typedef int Status;

struct ElemType;

typedef struct ElemType *PElemType;

typedef struct QNode
{
    PElemType data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct
{
    QueuePtr head;
    QueuePtr real;
} LinkQueue;

Status InitQueue(LinkQueue *Q)
{
    Q->head = (QueuePtr)malloc(sizeof(QNode));
    Q->head->data = NULL;
    Q->head->next = NULL;
    Q->real = Q->head;
    return OK;
}

Status ClearQueue(LinkQueue *Q)
{
    QueuePtr p = Q->head->next;
    while (p != NULL)
    {
        QueuePtr cur = p;
        p = p->next;
        free(cur);
    }
    Q->real = Q->head;
    return OK;
}

Status DestroyQueue(LinkQueue *Q)
{
    ClearQueue(Q);
    free(Q);
    return OK;
}

Status QueueEmpty(LinkQueue Q)
{
    if (Q.head == Q.real)
        return TRUE;
    return FALSE;
}

int QueueLength(LinkQueue Q)
{
    int len = 0;
    QueuePtr p = Q.head;
    while (p != NULL)
    {
        len++;
        p = p->next;
    }
    return len;
}

Status GetHead(LinkQueue Q, PElemType *e)
{
    if (QueueEmpty(Q) == TRUE)
        return OVERFLOW;
    *e = Q.head->next->data;
    return OK;
}

Status EnQueue(LinkQueue *Q, PElemType e)
{
    QueuePtr newNode = (QueuePtr)malloc(sizeof(QNode));
    newNode->data = e;
    newNode->next = Q->head->next;
    Q->head->next = newNode;
    if (QueueEmpty(*Q) == TRUE)
    {
        Q->real = newNode;
    }
    return OK;
}

Status DeQueue(LinkQueue *Q, PElemType *e)
{
    if (QueueEmpty(*Q) == TRUE)
    {
        return OVERFLOW;
    }
    else
    {
        *e = Q->head->next->data;
        if (Q->head->next == Q->real)
            Q->real = Q->head;
        Q->head->next = Q->head->next->next;
        return OK;
    }
}

void QueueTraverse(LinkQueue Q, void (*visit)(PElemType))
{
    QueuePtr p = Q.head->next;
    printf("Queue list is: ");
    while (p != NULL)
    {
        visit(p->data);
        p = p->next;
    }
    printf("\n");
}
