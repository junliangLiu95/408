#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;

typedef struct
{
    int *elem;
    int length;
    int listsize;
} SqList;

Status InitList_Sq(SqList *L)
{
    L->elem = (int *)malloc(LIST_INIT_SIZE * sizeof(int));
    if (!L->elem)
        exit(0);
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return OK;
}

Status DestroyList(SqList *L)
{
    free(L->elem);
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return OK;
}

void ClearList(SqList *L)
{
    L->length = 0;
}

int ListLength(SqList L)
{
    return L.length;
}

int *GetElem(SqList L, int i, int *e)
{
    if (i < 1 || i > L.length)
        exit(0);
    *e = L.elem[i - 1];
    return e;
}

bool compare(int a, int b)
{
    return a == b;
}

int LocateElem(SqList L, int e, bool (*compare)(int, int))
{
    int i = 0;
    for (; i < L.length; i++)
    {
        if ((*compare)(e, L.elem[i]))
        {
            return i + 1;
            break;
        }
    }
    return 0;
}

/*
    *q      *p
   0 1 2 3 4 5 N N N
    *q    *p
   0 1 2 3 4 5 5 N N
    *q  *p
   0 1 2 3 4 4 5 N N
    *q*p
   0 1 2 3 3 4 5 N N
    *p
    *q
   0 1 2 2 3 4 5 N N
  *p*q
   0 1 1 2 3 4 5 N N
end insert e
   0 e 1 2 3 4 5 N N
*/

void ListInsert_Sq(SqList *L, int i, int e)
{
    if (i < 1 || i > L->length + 1)
        exit(0);
    if (L->length >= L->listsize)
    {
        int *newbase = (int *)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(int));
        if (!newbase)
            exit(0);
        L->elem = newbase;
        L->listsize += LISTINCREMENT;
    }
    int *q = &(L->elem[i - 1]);
    for (int *p = &(L->elem[L->length - 1]); p >= q; --p)
    {
        *(p + 1) = *p;
    }
    *q = e;
    ++L->length;
}

/*
       *q  *p
    0 1 2 3 4 N N N
         *q*p
    0 1 3 3 4 N N N
           *p
           *q
    0 1 3 4 4 N N N
           *p*q
    0 1 3 4 N N N N
*/

int *ListDelete_Sq(SqList *L, int i, int *e)
{
    if (i < 1 || i > L->length)
        exit(0);
    int *q = &(L->elem[i - 1]);
    *e = *q;
    int *p = &(L->elem[L->length - 1]);
    for (; q <= p; q++)
    {
        *q = *(q + 1);
    }
    --L->length;
    return e;
}

/*
      *a
    La 2 3 8 9
      *b
    Lb 1 2 4 5 6 7
      *c
    Lc 1
*/

void MergeList_Sq(SqList La, SqList Lb, SqList *Lc)
{
    int *a = La.elem;
    int *b = Lb.elem;
    Lc->listsize = Lc->length = La.length + Lb.length;
    Lc->elem = (int *)malloc(Lc->listsize * sizeof(int));
    int *c = Lc->elem;
    if (!Lc->elem)
        exit(OVERFLOW);
    int *La_last = a + La.length - 1;
    int *Lb_last = b + Lb.length - 1;
    while (a <= La_last && b <= Lb_last)
    {
        if (*a <= *b)
        {
            *c++ = *a++;
        }
        else
        {
            *c++ = *b++;
        }
    }
    while (a <= La_last)
    {
        *c++ = *a++;
    }
    while (b <= Lb_last)
    {
        *c++ = *b++;
    }
}

int main()
{
    SqList a, b, c;
    InitList_Sq(&a);
    InitList_Sq(&b);
    InitList_Sq(&c);
    for (int i = 1; i <= 5; i++)
    {
        printf("%d ", i);
        ListInsert_Sq(&a, i, i);
    }
    printf("\n");
    for (int i = 1; i <= 10; i++)
    {
        printf("%d ", i * 2);
        ListInsert_Sq(&b, i, i * 2);
    }
    printf("\n");
    MergeList_Sq(a, b, &c);
    for (int i = 0; i < c.length; i++)
    {
        printf("%d ", c.elem[i]);
    }
}