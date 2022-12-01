#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;

typedef char TElemType;

typedef enum pointerTag
{
    Link,
    Thread
} pointerTag;

typedef struct BiThrNode
{
    TElemType data;
    struct BiThrNode *rchild, *lchild;
    pointerTag RTag, LTag;
} BiThrNode, *BiThrTree;

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

void CreateBiThrTree(BiThrTree *T, int *index)
{
    char c = getCharLoc(index);
    if (c != ' ')
    {
        *T = (BiThrTree)malloc(sizeof(BiThrNode));
        (*T)->data = c;
        CreateBiThrTree(&(*T)->lchild, index);
        CreateBiThrTree(&(*T)->rchild, index);
    }
}

void BiThrTree_InOrder(BiThrNode *T, void (*visit)(TElemType))
{
    if (T)
    {
        BiThrTree_InOrder(T->lchild, visit);
        visit(T->data);
        BiThrTree_InOrder(T->rchild, visit);
    }
}

/*
      lchild--1 Thrt rchild--7
      4 lchild ---Thrt
      7 rchild ---Thrt

             1
        2         3
      4    5   6     7
        9
*/

void InThreading(BiThrTree p, BiThrTree *pre)
{
    if (p)
    {
        InThreading(p->lchild, pre);
        if (!p->lchild)
        {
            p->LTag = Thread;
            p->lchild = (*pre);
        }
        if (!(*pre)->rchild)
        {
            (*pre)->RTag = Thread;
            (*pre)->rchild = p;
        }
        (*pre) = p;
        InThreading(p->rchild, pre);
    }
}

Status InOrderThreading(BiThrTree *Thrt, BiThrTree T)
{
    *Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
    (*Thrt)->LTag = Link;
    (*Thrt)->RTag = Thread;
    (*Thrt)->lchild = (*Thrt);
    if (!T)
    {
        (*Thrt)->lchild = (*Thrt);
    }
    else
    {
        (*Thrt)->lchild = T;
        BiThrTree pre = (*Thrt);
        InThreading(T, &pre);
        (*Thrt)->rchild = pre;
        pre->RTag = Thread;
        pre->rchild = (*Thrt);
    }
    return OK;
}

Status InOrderThrTreeTraverse(BiThrTree T)
{
    BiThrTree p = T->lchild;
    while (p != T)
    {
        while (p->LTag == Link)
        {
            p = p->lchild;
        }
        printf("%c,", p->data);
        while (p->RTag == Thread && p->rchild != T)
        {
            printf("%c,", p->rchild->data);
            p = p->rchild;
        }
        p = p->rchild;
    }
    return OK;
}

BiThrTree BiThrTree_InOrderPre(BiThrTree T)
{
    if (T->LTag == Thread)
        return T->lchild;
    BiThrTree p = T->lchild;
    while (p->RTag == Link)
    {
        p = p->rchild;
    }
    return p;
}

BiThrTree BiThrTree_InOrderNext(BiThrTree T)
{
    if (T->RTag == Thread)
        return T->rchild;
    BiThrTree p = T->rchild;
    while (p->LTag == Link)
    {
        p = p->lchild;
    }
    return p;
}
