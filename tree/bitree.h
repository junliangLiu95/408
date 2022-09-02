#include <stdio.h>
#include <stdlib.h>
#include "../queue/Queue.h"

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

typedef struct ElemType
{
    BiTree data;
} ElemType;

void CreateBiTree(BiTree *T, int *index);
Status PreOrderTraverse(BiTree T, Status (*visit)(TElemType e));
Status InOrderTraverse(BiTree T, Status (*visit)(TElemType e));
Status PostOrderTraverse(BiTree T, Status (*visit)(TElemType e));
Status LevelOrderTraverse(BiTree T, Status (*visit)(TElemType e));

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

Status PreOrderTraverse(BiTree T, Status (*visit)(TElemType))
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

Status InOrderTraverse(BiTree T, Status (*visit)(TElemType))
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

Status PostOrderTraverse(BiTree T, Status (*visit)(TElemType))
{
    if (T)
    {
        InOrderTraverse(T->lchild, visit);
        InOrderTraverse(T->rchild, visit);
        visit(T->data);
    }
    else
    {
        printf(" ,");
    }
    return OK;
}

Status LevelOrderTraverse(BiTree T, Status (*visit)(TElemType e))
{
    LinkQueue q1, q2;
    InitQueue(&q1);
    InitQueue(&q2);
    PElemType e = (PElemType)malloc(sizeof(ElemType));
    e->data = T;
    EnQueue(&q1, e);
    int group = 1;
    while (QueueEmpty(q1) == FALSE || QueueEmpty(q2) == FALSE)
    {
        if (group == 1)
        {
            PElemType p = (PElemType)malloc(sizeof(ElemType));
            DeQueue(&q1, &p);
            visit(p->data->data);
            if (p->data->lchild)
            {
                PElemType e = (PElemType)malloc(sizeof(ElemType));
                e->data = p->data->lchild;
                EnQueue(&q2, e);
            }
            if (p->data->rchild)
            {
                PElemType e = (PElemType)malloc(sizeof(ElemType));
                e->data = p->data->rchild;
                EnQueue(&q2, e);
            }
            if (QueueEmpty(q1) == TRUE)
            {
                group = 2;
            }
        }
        if (group == 2)
        {
            PElemType p = (PElemType)malloc(sizeof(ElemType));
            DeQueue(&q2, &p);
            visit(p->data->data);
            if (p->data->lchild)
            {
                PElemType e = (PElemType)malloc(sizeof(ElemType));
                e->data = p->data->lchild;
                EnQueue(&q1, e);
            }
            if (p->data->rchild)
            {
                PElemType e = (PElemType)malloc(sizeof(ElemType));
                e->data = p->data->rchild;
                EnQueue(&q1, e);
            }
            if (QueueEmpty(q2) == TRUE)
            {
                group = 1;
            }
        }
    }
    return OK;
}