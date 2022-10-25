#include "Queue.h"

typedef struct QElemType
{
    int data;
} QElemType;

void visit(PQElemType p)
{
    printf("%d ", p->data);
}

int main()
{
    LinkQueue Q;
    InitQueue(&Q);
    Status isEmpty = QueueEmpty(Q);
    printf("empty: %d\n", isEmpty);
    for (int i = 1; i < 5; i++)
    {
        PQElemType e = (PQElemType)malloc(sizeof(QElemType));
        e->data = i;
        EnQueue(&Q, e);
    }
    isEmpty = QueueEmpty(Q);
    printf("empty: %d\n", isEmpty);
    QueueTraverse(Q, visit);
    PQElemType b = (PQElemType)malloc(sizeof(QElemType));
    GetHead(Q, &b);
    printf("head val : %d\n", b->data);
    for (int i = 1; i < 5; i++)
    {
        if (QueueEmpty(Q) == FALSE)
        {
            PQElemType c = (PQElemType)malloc(sizeof(QElemType));
            DeQueue(&Q, &c);
            printf("delete val: %d\n", c->data);
            PQElemType e = (PQElemType)malloc(sizeof(QElemType));
            e->data = i;
            EnQueue(&Q, e);
        }
    }
    QueueTraverse(Q, visit);
    return 0;
}