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

typedef struct LNode
{
    int data;
    struct LNode *next;
} LNode;

/*
    L -> NULL

    L -> ([][*next]) -> NULL
    insert e
    L -> ([][*next]) -> ([e][*next]) -> NULL
*/

void CreateList_LNode(LNode *L, int n)
{
    L = (LNode *)malloc(sizeof(LNode));
    L->next = NULL;
    for (int i = 0; i < n; i++)
    {
        LNode *p = (LNode *)malloc(sizeof(LNode));
        int c;
        scanf("%d", &c);
        printf("%d", c);
        p->data = c;
        p->next = L->next;
        L->next = p;
    }
}
/*       data
    L -> *next -> NULL
*/

Status GetElem_L(LNode *L, int i, char *e)
{
    LNode *p = L->next;
    int j = 1;
    for (int j = 1; p && j < i; j++)
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
    LNode *L;
    CreateList_LNode(L, 5);
    for (int i = 1; i < 5; i++)
    {
        char *a;
        GetElem_L(L, i, a);
        printf("%s ", a);
    }
}