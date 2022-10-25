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

typedef struct
{
    int *base;
    int *top;
    int stacksize;
} SqStack;

struct SElemType;

typedef struct SElemType *PSElemType;

typedef struct LNode
{
    PSElemType data;
    struct LNode *next;
} LNode;

typedef struct
{
    struct LNode *top;
} LNodeStack;

/*
                                           top ->
               [ ]           [      ]             [ elem ]
               [ ]  top  ->  [      ]             [ elem ]
base & top ->  [ ]  base ->  [ elem ]    base ->  [ elem ]

*/

Status InitStack(SqStack *S)
{
    S->base = (int *)malloc(STACK_INIT_SIZE * sizeof(int));
    if (!S->base)
        exit(OVERFLOW);
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return OK;
}

Status Push(SqStack *S, int s)
{
    if (S->top - S->base > S->stacksize)
    {
        S->base = (int *)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(int));
        if (!S->base)
            exit(OVERFLOW);
        S->stacksize += STACKINCREMENT;
    }
    *S->top++ = s;
    return OK;
}

Status Pop(SqStack *S, int *s)
{
    if (S->base == S->top)
        return ERROR;
    *s = *--S->top;
    return OK;
}

Status ClearStack(SqStack *S)
{
    S->top = S->base;
    return OK;
}

void StackTraverse(SqStack S, void (*visit)(int))
{
    int *p = S.top;
    if (p == S.base)
        return;
    while (p != S.base)
    {
        visit(*--p);
    };
    printf("\n");
}

Status InitLNodeStack(LNodeStack *S)
{
    S->top = NULL;
    return OK;
}

Status ClearLNodeStack(LNodeStack *S)
{
    LNode *p = S->top;
    while (p)
    {
        LNode *tmp = p;
        p = p->next;
        free(tmp);
    }
    S->top = NULL;
    return OK;
}

Status StackEmpty(LNodeStack S)
{
    return S.top == NULL ? TRUE : FALSE;
}

Status LNodeStack_Push(LNodeStack *S, PSElemType e)
{
    LNode *top = S->top;
    LNode *newLNode = (LNode *)malloc(sizeof(LNode));
    newLNode->data = e;
    S->top = newLNode;
    newLNode->next = top;
    return OK;
}

PSElemType LNodeStack_Pop(LNodeStack *S)
{
    if (!S->top)
        exit(OVERFLOW);
    PSElemType e = S->top->data;
    S->top = S->top->next;
    return e;
}

void LNodeStackTraverse(LNodeStack S, void (*visit)(PSElemType))
{
    LNode *p = S.top;
    while (p)
    {
        visit(p->data);
        p = p->next;
    }
    printf("\n");
}

Status LNodeStack_exsit(LNodeStack S, PSElemType P, Status (*compare)(PSElemType, PSElemType))
{
    LNode *p = S.top;
    while (p != NULL)
    {
        Status same = compare(p->data, P);
        if (same == OK)
            return TRUE;
        p = p->next;
    }
    return FALSE;
}

/*
    N    N div 8    N mod 8
   1348    168       4
    168     21       0
     21      2       5
      2      0       2
*/

SqStack converion()
{
    SqStack S;
    InitStack(&S);
    int N;
    scanf("%d", &N);
    while (N)
    {
        Push(&S, N % 8);
        N = N / 8;
    }
    return S;
}