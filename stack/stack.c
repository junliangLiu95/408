#include "stack.h"

typedef struct SElemType
{
    int data;
} SElemType;

void visit(int p)
{
    printf("%d ", p);
}

void visit_LNodeStack(PSElemType p)
{
    printf("%d\n", p->data);
}

int main()
{
    SqStack S;
    int s;
    LNodeStack S2;
    PSElemType s2 = (PSElemType)malloc(sizeof(SElemType));
    PSElemType s3;
    s2->data = 1;
    InitStack(&S);
    Push(&S, 1);
    StackTraverse(S, visit);
    Pop(&S, &s);
    printf("%d\n", s);
    StackTraverse(S, visit);
    LNodeStack_Push(&S2, s2);
    LNodeStackTraverse(S2, visit_LNodeStack);
    SqStack S3 = converion();
    StackTraverse(S3, visit);
    return 0;
}