#include <stdio.h>
#include <stdlib.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;

typedef struct LNode
{
    int data;
    struct LNode *next;
} LNode, *LinkList;

/*
    L -> NULL

    L -> ([][*next]) -> NULL
    insert e
    L -> ([][*next]) -> ([e][*next]) -> NULL
*/

void CreateList_LNode(LinkList L, int n)
{
    L->next = NULL;
    for (int i = 0; i < n; i++)
    {
        LinkList p = (LinkList)malloc(sizeof(LNode));
        scanf("%d", &p->data);
        p->next = L->next;
        L->next = p;
    }
}

void PrintAllMember_LNode(LinkList L)
{
    LinkList p = L->next;
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

/*       data
    L -> *next -> NULL

    L -> 4 -> 3 -> NULL
*/

Status GetElem_LNode(LinkList L, int i, int *e)
{
    LinkList p = L->next;
    for (int j = 1; p != NULL && j < i; j++)
    {
        p = p->next;
    }
    if (p)
    {
        *e = p->data;
    }
    else
    {
        return ERROR;
    }
    return OK;
}

/*
    L -> 1 -> 2 -> NULL
    insert e
    p
    L -> 1 -> 2 -> NULL
    e.next =  p.next;p.next = *e;
*/

Status ListInsert_LNode(LinkList L, int i, int e)
{
    LinkList p = L;
    LinkList new = (LinkList)malloc(sizeof(LNode));
    new->data = e;
    int j = 0;
    for (; p != NULL && j < i - 1; j++)
    {
        p = p->next;
    }
    //确保 i>=1
    if (p && j == i - 1)
    {
        new->next = p->next;
        p->next = new;
        return OK;
    }
    else
    {
        return OVERFLOW;
    }
}

/*
    p    q
    L -> 1 -> 2 -> NULL
*/

Status ListDelete_LNode(LinkList L, int i, int *e)
{
    LinkList p, q;
    p = L;
    int j = 0;
    for (; p && j < i - 1; j++)
    {
        p = p->next;
    }
    if (p && j == i - 1)
    {
        q = p->next;
        p->next = p->next->next;
        *e = q->data;
        free(q);
        return OK;
    }
    else
    {
        return OVERFLOW;
    }
}

/*  pc    pa
    La -> 1 -> 3 -> NULL
          pb
    Lb -> 1 -> 2 -> 5 -> NULL
*/

void MergeList_LNode(LinkList La, LinkList Lb, LinkList Lc)
{
    LinkList pa, pb, pc;
    pa = La->next;
    pb = Lb->next;
    Lc = pc = La;
    while (pa && pb)
    {
        if (pa->data <= pb->data)
        {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else
        {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }
    pc->next = pa ? pa : pb;
    free(Lb);
}

int main()
{
    int a;
    LinkList La = (LinkList)malloc(sizeof(LNode));
    LinkList Lb = (LinkList)malloc(sizeof(LNode));
    LinkList Lc = (LinkList)malloc(sizeof(LNode));
    CreateList_LNode(La, 2);
    CreateList_LNode(Lb, 3);
    PrintAllMember_LNode(La);
    PrintAllMember_LNode(Lb);
    MergeList_LNode(La, Lb, Lc);
    PrintAllMember_LNode(La);
}