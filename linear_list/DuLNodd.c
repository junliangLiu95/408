#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;

typedef struct DuLNode
{
    int data;
    struct DuLNode *prior;
    struct DuLNode *next;
} DuLNode, *DuLinkList;

/*
 *L <-> * [] * <-> * [] * <-> *L
 */

void CreateList_DuLNode(DuLinkList L, int len)
{
    DuLinkList pNow = L;
    for (int i = 0; i < len; i++)
    {
        DuLinkList newNode = (DuLinkList)malloc(sizeof(DuLNode));
        newNode->prior = pNow;
        newNode->next = L;
        pNow->next = newNode;
        L->prior = newNode;
        scanf("%d", &newNode->data);
        pNow = newNode;
    }
}

void PrintList_DuLNode(DuLinkList L)
{
    DuLinkList p = L->next;
    while (p != L)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

/*

    L <-> [1] <-> [2] <-> L
    insert 3 before index 1
    L <-> [3] <-> [1] <-> [2] <-> L
*/

Status InsertList_DuLNode(DuLinkList L, int i, int e)
{
    DuLinkList p = L->next;
    int j = 1;
    for (; j < i && p != L; j++)
    {
        p = p->next;
    }
    if (j != i || p == L)
    {
        return OVERFLOW;
    }
    else
    {
        DuLinkList new = (DuLinkList)malloc(sizeof(DuLNode));
        new->prior = p->prior;
        new->next = p;
        p->prior->next = new;
        p->prior = new;
        new->data = e;
        return OK;
    }
}

/*

    L <-> [1] <-> [2] <-> L
    delete index 1
    L <-> [2] <-> L

*/

Status DeleteList_DuLNode(DuLinkList L, int i, int *e)
{
    DuLinkList p = L->next;
    int j = 1;
    for (; j < i && p != L; j++)
    {
        p = p->next;
    }
    if (j != i || p == L)
    {
        return OVERFLOW;
    }
    else
    {
        p->prior->next = p->next;
        p->next->prior = p->prior;
        *e = p->data;
        free(p);
        return OK;
    }
}

int main()
{
    int e;
    DuLinkList A = (DuLinkList)malloc(sizeof(DuLNode));
    CreateList_DuLNode(A, 5);
    PrintList_DuLNode(A);
    InsertList_DuLNode(A, 1, 6);
    PrintList_DuLNode(A);
    DeleteList_DuLNode(A, 2, &e);
    PrintList_DuLNode(A);
    return 0;
}