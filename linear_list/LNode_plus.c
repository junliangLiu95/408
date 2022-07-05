#include <stdio.h>
#include <stdlib.h>

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
} LNode, *Link, *Position;

typedef struct
{
    Link head, tail;
    int len;
} LinkList;

Status MakeNode(Link p, int e)
{
    p = (Link)malloc(sizeof(LNode));
    if (!p)
    {
        return ERROR;
    }
    p->data = e;
    return OK;
}

void FreeNode(Link p)
{
    free(p);
}

Status InitList(LinkList L)
{
    Link p = (Link)malloc(sizeof(LNode));
    p->next = NULL;
    L.head = p;
    L.tail = p;
    L.len = 0;
    return OK;
}

Status InsFirst(Link h, Link s)
{
    s->next = h->next;
    h->next = s;
    return OK;
}

Status DelFirst(Link h, Link q)
{
    q = h->next;
    h->next = h->next->next;
    return OK;
}

Status Append(LinkList L, Link s)
{
    L.tail->next = s;
    Position tail = s;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }
    L.tail = tail;
}

int main()
{
    return 0;
}