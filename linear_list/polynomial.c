#include <stdio.h>
#include <stdlib.h>
#include "LNode_plus.h"

typedef struct ElemType
{
    float coef;
    int expn;
} term, ElemType;

int main()
{
    PElemType pe = (PElemType)malloc(sizeof(ElemType));
    pe->coef = 1;
    pe->expn = 1;
    Link p = MakeNode(pe);
    printf("%d", p->data->expn);
    return 0;
}