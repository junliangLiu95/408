#include <stdio.h>
#include <stdlib.h>
#include "../queue/Queue.h"
#include "../stack/stack.h"

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;

typedef char TElemType;

typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef struct QElemType
{
    BiTree data;
} ElemType;

typedef struct SElemType
{
    BiTree data;
} SElemType;

void CreateBiTree(BiTree *T, int *index);
Status PreOrderTraverse(BiTree T, void (*visit)(TElemType e));
Status InOrderTraverse(BiTree T, void (*visit)(TElemType e));
Status PostOrderTraverse(BiTree T, void (*visit)(TElemType e));
Status LevelOrderTraverse(BiTree T, void (*visit)(TElemType e));

/*
             1
        2         3
      4    5   6     7
        9
*/

char getCharLoc(int *index)
{
    char c[] = "124 9  5  36  7  ";
    return c[(*index)++];
}

void CreateBiTree(BiTree *T, int *index)
{
    char c = getCharLoc(index);
    if (c != ' ')
    {
        *T = (BiTree)malloc(sizeof(BiTNode));
        (*T)->data = c;
        CreateBiTree(&(*T)->lchild, index);
        CreateBiTree(&(*T)->rchild, index);
    }
}

Status PreOrderTraverse(BiTree T, void (*visit)(TElemType))
{
    if (T)
    {
        visit(T->data);
        PreOrderTraverse(T->lchild, visit);
        PreOrderTraverse(T->rchild, visit);
    }
    else
    {
        printf(" ,");
    }
    return OK;
}

Status InOrderTraverse(BiTree T, void (*visit)(TElemType))
{
    if (T)
    {
        InOrderTraverse(T->lchild, visit);
        visit(T->data);
        InOrderTraverse(T->rchild, visit);
    }
    else
    {
        printf(" ,");
    }
    return OK;
}

Status PostOrderTraverse(BiTree T, void (*visit)(TElemType))
{
    if (T)
    {
        PostOrderTraverse(T->lchild, visit);
        PostOrderTraverse(T->rchild, visit);
        visit(T->data);
    }
    else
    {
        printf(" ,");
    }
    return OK;
}

Status LevelOrderTraverse(BiTree T, void (*visit)(TElemType e))
{
    LinkQueue q;
    InitQueue(&q);
    PQElemType e = (PQElemType)malloc(sizeof(ElemType));
    e->data = T;
    EnQueue(&q, e);
    while (QueueEmpty(q) == FALSE)
    {
        PQElemType p = (PQElemType)malloc(sizeof(ElemType));
        DeQueue(&q, &p);
        visit(p->data->data);
        if (p->data->lchild)
        {
            PQElemType e = (PQElemType)malloc(sizeof(ElemType));
            e->data = p->data->lchild;
            EnQueue(&q, e);
        }
        if (p->data->rchild)
        {
            PQElemType e = (PQElemType)malloc(sizeof(ElemType));
            e->data = p->data->rchild;
            EnQueue(&q, e);
        }
    }
    return OK;
}

Status preOrderTraverseNonRecur(BiTree T, void (*visit)(TElemType e))
{
    LNodeStack S;
    InitLNodeStack(&S);
    PSElemType e = (PSElemType)malloc(sizeof(SElemType));
    e->data = T;
    LNodeStack_Push(&S, e);
    while (StackEmpty(S) == FALSE)
    {
        PSElemType p;
        p = LNodeStack_Pop(&S);
        visit(p->data->data);
        if (p->data->rchild)
        {
            PSElemType e = (PSElemType)malloc(sizeof(SElemType));
            e->data = p->data->rchild;
            LNodeStack_Push(&S, e);
        }
        if (p->data->lchild)
        {
            PSElemType e = (PSElemType)malloc(sizeof(SElemType));
            e->data = p->data->lchild;
            LNodeStack_Push(&S, e);
        }
    }
    return OK;
}

Status inOrderTraverseNonRecur(BiTree T, void (*visit)(TElemType e))
{
    LNodeStack S;
    InitLNodeStack(&S);
    BiTree current = T;
    while (current || StackEmpty(S) == FALSE)
    {
        if (current)
        {
            PSElemType e = (PSElemType)malloc(sizeof(SElemType));
            e->data = current;
            LNodeStack_Push(&S, e);
            current = current->lchild;
        }
        else
        {
            BiTree p = LNodeStack_Pop(&S)->data;
            visit(p->data);
            current = p->rchild;
        }
    }
    return OK;
}

void reverseVisitStack(LNode *n)
{
    if (n)
    {
        printf("%c,", n->data->data->data);
        reverseVisitStack(n->next);
    }
}

Status postOrderTraverseNonRecur(BiTree T, void (*visit)(TElemType e))
{
    LNodeStack S1, S2;
    InitLNodeStack(&S1);
    InitLNodeStack(&S2);
    PSElemType e = (PSElemType)malloc(sizeof(SElemType));
    e->data = T;
    LNodeStack_Push(&S1, e);
    while (StackEmpty(S1) == FALSE)
    {
        PSElemType e = LNodeStack_Pop(&S1);
        LNodeStack_Push(&S2, e);
        if (e->data->lchild)
        {
            PSElemType le = (PSElemType)malloc(sizeof(SElemType));
            le->data = e->data->lchild;
            LNodeStack_Push(&S1, le);
        }
        if (e->data->rchild)
        {
            PSElemType re = (PSElemType)malloc(sizeof(SElemType));
            re->data = e->data->rchild;
            LNodeStack_Push(&S1, re);
        }
    }
    reverseVisitStack(S2.top);
    return OK;
}