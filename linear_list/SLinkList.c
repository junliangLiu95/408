#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;

typedef struct
{
    int data;
    int cur;
} SLinkList[MAXSIZE];

/*
    闲置表          插入节点          插入节点          删除节点
        data cur        data cur        data cur        data cur
    0   []   [1]    0   []   [2]    0   []   [3]    0   []   [2]
    1   []   [2]    1   [1]  [0]    1   [1]  [2]    1   [1]  [0]
    2   []   [3]    2   []   [3]    2   [2]  [0]    2   [2]  [3]
    3   []   [4]    3   []   [4]    3   []   [4]    3   []   [4]
    4   []   [0]    4   []   [0]    4   []   [0]    4   []   [0]
*/

void Reserve_SL(SLinkList space)
{
    for (int i = 0; i < MAXSIZE - 1; i++)
    {
        space[i].cur = i + 1;
    }
    space[MAXSIZE - 1].cur = 0;
}

int Malloc_SL(SLinkList space)
{
    int i = space[0].cur;
    if (i)
    {
        space[0].cur = space[i].cur;
        return i;
    }
    return 0;
}

void Free_SL(SLinkList space, int index)
{
    space[index].cur = space[0].cur;
    space[0].cur = index;
}

int InitSpace_SL(SLinkList space)
{
    int head = Malloc_SL(space);
    space[head].data = 0;
    space[head].cur = 0;
    return head;
}

void Insert_SL(SLinkList space, int head, int i, int e)
{
    if (i < 1)
        return;
    int headTmp = head;
    for (int j = 1; j < i; j++)
    {
        headTmp = space[headTmp].cur;
    }
    int insertIndex = Malloc_SL(space);
    space[insertIndex].data = e;
    space[insertIndex].cur = space[headTmp].cur;
    space[headTmp].cur = insertIndex;
}

Status Delete_SL(SLinkList space, int head, int i, int *e)
{
    int p = head;
    if (p == 0)
        return OVERFLOW;
    for (int j = 1; j < i; j++)
    {
        p = space[p].cur;
    }
    int next = space[p].cur;
    space[p].cur = space[next].cur;
    *e = space[next].data;
    Free_SL(space, next);
    return OK;
}

void Print_SL(SLinkList space, int head)
{
    int freeSpaceP = 0;
    printf("free space index: ");
    while (space[freeSpaceP].cur)
    {
        printf("%d", freeSpaceP);
        freeSpaceP = space[freeSpaceP].cur;
    }
    printf("%d", freeSpaceP);
    printf("\n");
    int dataSpaceP = head;
    while (space[dataSpaceP].cur)
    {
        printf("index : %d val: %d \n", dataSpaceP, space[dataSpaceP].data);
        dataSpaceP = space[dataSpaceP].cur;
    }
    printf("index : %d val: %d \n", dataSpaceP, space[dataSpaceP].data);
}

int main()
{
    SLinkList s;
    int e;
    Reserve_SL(s);
    int head = InitSpace_SL(s);
    Insert_SL(s, head, 1, 1);
    Insert_SL(s, head, 2, 2);
    Print_SL(s, head);
    Delete_SL(s, head, 2, &e);
    printf("delete item val: %d\n", e);
    Print_SL(s, head);
    return 0;
}
