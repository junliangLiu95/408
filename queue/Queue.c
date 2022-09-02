#include "Queue.h"

typedef struct ElemType
{
    int data;
} ElemType;

void visit(PElemType p)
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
        PElemType e = (PElemType)malloc(sizeof(ElemType));
        e->data = i;
        EnQueue(&Q, e);
    }
    isEmpty = QueueEmpty(Q);
    printf("empty: %d\n", isEmpty);
    QueueTraverse(Q, visit);
    PElemType b = (PElemType)malloc(sizeof(ElemType));
    GetHead(Q, &b);
    printf("head val : %d\n", b->data);
    for (int i = 1; i < 5; i++)
    {
        if (QueueEmpty(Q) == FALSE)
        {
            PElemType c = (PElemType)malloc(sizeof(ElemType));
            DeQueue(&Q, &c);
            printf("delete val: %d\n", c->data);
            PElemType e = (PElemType)malloc(sizeof(ElemType));
            e->data = i;
            EnQueue(&Q, e);
        }
    }
    QueueTraverse(Q, visit);
    return 0;
}