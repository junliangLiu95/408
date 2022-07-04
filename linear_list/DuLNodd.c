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
}

int main()
{
    DuLinkList A = (DuLinkList)malloc(sizeof(DuLNode));
    CreateList_DuLNode(A, 5);
    PrintList_DuLNode(A);
    return 0;
}