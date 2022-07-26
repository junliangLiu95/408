#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;

struct ElemType;

typedef struct ElemType *PElemType;

typedef struct LNode
{
    PElemType data;
    struct LNode *next;
} LNode, *Link, *Position;

typedef struct LinkList
{
    Link head, tail;
    int len;
} LinkList;

Link MakeNode(PElemType e)
{
    Link p = (Link)malloc(sizeof(LNode));
    p->data = e;
    return p;
}

void FreeNode(Link p)
{
    free(p);
}

Status InitList(LinkList *L)
{
    Link p = (Link)malloc(sizeof(LNode));
    p->next = NULL;
    L->head = p;
    L->tail = p;
    L->len = 0;
    return OK;
}

Status InsFirst(LinkList *L, Link h, Link s)
{
    s->next = h->next;
    h->next = s;
    L->len++;
    return OK;
}

Status DelFirst(LinkList *L, Link h)
{
    Link q = h->next;
    h->next = h->next->next;
    free(q);
    L->len--;
    return OK;
}

Status Append(LinkList *L, Link s)
{
    L->tail->next = s;
    Position tail = s;
    int lenS = 1;
    while (tail->next != NULL)
    {
        tail = tail->next;
        lenS++;
    }
    L->len += lenS;
    L->tail = tail;
    return OK;
}

Status ListEmpty(LinkList L)
{
    return L.head == L.tail ? TRUE : FALSE;
}

Status Remove(LinkList *L, Link *q)
{
    if (ListEmpty(*L) == TRUE)
        return OVERFLOW;
    *q = L->tail;
    Link pre = L->head;
    while (pre->next != L->tail)
    {
        pre = pre->next;
    }
    pre->next = NULL;
    L->tail = pre;
    L->len--;
    return OK;
}

Position PriorPos(LinkList L, Link p)
{
    if (p == L.head)
        return NULL;
    Position prior = L.head;
    while (prior->next != p)
    {
        prior = prior->next;
    }
    return prior;
}

Status InsBefore(LinkList *L, Link p, Link s)
{
    Position pre = PriorPos(*L, p);
    if (!pre)
    {
        return OVERFLOW;
    }
    else
    {
        pre->next = s;
        s->next = p;
        L->len++;
        return OK;
    }
}

Status InsAfter(LinkList *L, Link p, Link s)
{
    s->next = p->next;
    p->next = s;
    L->len++;
    return OK;
}

int ListLength(LinkList L)
{
    return L.len;
}

Position GetHead(LinkList L)
{
    return L.head;
}

Position GetLast(LinkList L)
{
    return L.tail;
}

Position NextPos(LinkList L, Link p)
{
    return p->next;
}

Status LocatePos(LinkList L, int i, Link *p)
{
    if (i > L.len)
        return ERROR;
    Position pos = L.head->next;
    int j = 1;
    while (j != i)
    {
        pos = pos->next;
        j++;
    }
    *p = pos;
    return OK;
}

Position LocateElem(LinkList L, PElemType e, Status (*compare)(PElemType, PElemType))
{
    Position p = L.head;
    while (p->next != NULL)
    {
        if (compare(p->next->data, e))
        {
            return p->next;
        }
        p = p->next;
    }
    return NULL;
}

void Delete(LinkList *L, Position p)
{
    if (p == L->head)
        exit(0);
    Position prior = L->head;
    while (prior->next != p)
    {
        prior = prior->next;
    }
    prior->next = p->next;
    L->len--;
    if (p == L->tail)
        L->tail = prior;
}

/*
    head -> 1 -> 2 -> null
*/

void traverse(Link preLink)
{
    Link curLink = preLink->next;
    if (curLink)
    {
        traverse(curLink);
        curLink->next = preLink;
    }
}

void Reversal(LinkList *L)
{
    if (L->head == L->tail)
        return;
    traverse(L->head->next);
    Link tmp = L->tail;
    L->tail = L->head->next;
    L->tail->next = NULL;
    L->head->next = tmp;
}

void Reversal_V2(LinkList *L)
{
    if (L->head == L->tail)
        return;
    Link prev = NULL;
    Link current = L->head->next;
    Link next = NULL;
    while (current)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    Link tmp = L->tail;
    L->tail = L->head->next;
    L->head->next = tmp;
}

void ListTraverse(LinkList L, void (*visit)(PElemType))
{
    Link p = L.head;
    while (p->next != NULL)
    {
        visit(p->next->data);
        p = p->next;
    }
    printf("\n");
}