#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef struct
{
    int *elem;
    int length;
    int listsize;
} SqList;

int InitList_Sq(SqList *L)
{
    L->elem = (int *)malloc(LIST_INIT_SIZE * sizeof(int));
    if (!L->elem)
        exit(0);
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return 1;
}

int DestroyList(SqList *L)
{
    free(L->elem);
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return 0;
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

int main()
{
    SqList p;
    InitList_Sq(&p);
    for (int i = 1; i <= 5; i++)
    {
        printf("%d", i);
        ListInsert_Sq(&p, i, i);
    }
    int index = LocateElem(p, 4, compare);
    printf("%d", index);
}