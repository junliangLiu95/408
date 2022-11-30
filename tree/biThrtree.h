#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;

typedef char TElemType;

typedef enum pointerTag
{
    Link,
    Thread
} pointerTag;

typedef struct BiThrNode
{
    TElemType data;
    struct BiThrNode *rchild, *lchild;
    pointerTag RTag, LTag;
} BiThrNode, *BiThrTree;

/*
             1
        2         3
      4    5   6     7
        9
*/

char getCharLoc(int *index)
{
    char c[] = "124 9  5  36  7  ";
    return c[(*index)++];
}

void CreateBiThrTree(BiThrTree *T, int *index)
{
    char c = getCharLoc(index);
    if (c != ' ')
    {
        *T = (BiThrTree)malloc(sizeof(BiThrNode));
        (*T)->data = c;
        CreateBiThrTree(&(*T)->lchild, index);
        CreateBiThrTree(&(*T)->rchild, index);
    }
}

void BiThrTree_PreOrder(BiThrNode *T, void (*visit)(TElemType))
{
    if (T)
    {
        visit(T->data);
        BiThrTree_PreOrder(T->lchild, visit);
        BiThrTree_PreOrder(T->rchild, visit);
    }
}