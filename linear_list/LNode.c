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

void PrintAllMember(LinkList L)
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

Status GetElem_L(LinkList L, int i, int *e)
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

int main()
{
    int a;
    LinkList Mylist = (LinkList)malloc(sizeof(LNode));
    CreateList_LNode(Mylist, 2);
    PrintAllMember(Mylist);
    Status status = GetElem_L(Mylist, 3, &a);
    printf("%d\n", status);
    printf("%d", a);
}