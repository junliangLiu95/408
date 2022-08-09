#include "SqQueue.h"

int main()
{
    SqQueue Q;
    InitQueue(&Q);
    for (int i = 0; i < 5; i++)
    {
        EnQueue(&Q, i);
    }
    printf("queue len : %d \n", QueueLength(Q));
    QueueTraverse(Q);
    int e;
    DeQueue(&Q, &e);
    printf("delete queue elem : %d \n", e);
    DeQueue(&Q, &e);
    DeQueue(&Q, &e);
    DeQueue(&Q, &e);
    EnQueue(&Q, 7);
    EnQueue(&Q, 8);
    QueueTraverse(Q);
    return 0;
}