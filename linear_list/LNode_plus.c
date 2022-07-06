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

typedef struct LinkList
{
    Link head, tail;
    int len;
} LinkList;

Link MakeNode(int e)
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
    p->data = 0;
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
    (*L).tail->next = s;
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

Status SetCurElem(Link p, int e)
{
    p->data = e;
    return OK;
}

int GetCurElem(Link p)
{
    return p->data;
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

Position LocateElem(LinkList L, int e, Status (*compare)(int, int))
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

void ListTraverse(LinkList L)
{
    Link p = L.head;
    while (p->next != NULL)
    {
        printf("%d ", p->next->data);
        p = p->next;
    }
    printf("\n");
}

Status compare(int a, int b)
{
    return a == b ? TRUE : FALSE;
}

int main()
{
    LinkList L;
    InitList(&L);
    for (int i = 0; i < 5; i++)
    {
        Link p = MakeNode(i + 1);
        Append(&L, p);
    }
    printf("Origin LinkList:\n");
    ListTraverse(L);
    Link p1 = MakeNode(8);
    InsFirst(&L, L.head, p1);
    printf("Insert 8 as first LNode:\n");
    ListTraverse(L);
    printf("Delete first LNode:\n");
    DelFirst(&L, L.head);
    ListTraverse(L);
    Link p2;
    Remove(&L, &p2);
    printf("remove last LNode, item val = %d\n", p2->data);
    ListTraverse(L);
    Link p3;
    LocatePos(L, 2, &p3);
    printf("Locate 2nd LNode value = %d\n", p3->data);
    Position p4 = PriorPos(L, p3);
    printf("2nd LNode's prior LNode's value = %d\n", p4->data);
    Link p5 = MakeNode(8);
    InsBefore(&L, p3, p5);
    printf("Insert 8 before 2nd LNode:\n");
    ListTraverse(L);
    Link p6 = MakeNode(8);
    printf("Insert 8 after 2nd LNode:\n");
    InsAfter(&L, p3, p6);
    ListTraverse(L);
    Position p7 = LocateElem(L, 8, compare);
    printf("Locate value 8 Link's val = %d", p7->data);
    return 0;
}