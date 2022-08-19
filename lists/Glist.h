#include <stdio.h>
#include <stdlib.h>
#include "../stack/stack.h"

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;

typedef enum
{
    ATOM,
    LIST
} ElemTag;

typedef char AtomType;

typedef struct GLNode
{
    ElemTag tag;
    union
    {
        AtomType atom;
        struct GLNode *hp;
    };
    struct GLNode *tp;

} * GList, GLNode;

typedef struct SElemType
{
    struct GLNode *data;
} SElemType;

/*
    LIST:           ATOM
    [1][hp][tp]     [0][atom][tp]

    A()
    B('e')
    C('a',('b','c','d'))
    D(A,B,C)

    A[]
    D[1][ ][^]
         |
         *[1][^][ ]--*B[1][ ][ ] ---------*C[1][ ][^]
                           |                    |
                           *[0]['e'][^]         *[0]['a'][ ]--*[1][ ][^]
                                                                   |
                                                                   *[0]['b'][ ]--*[0]['c'][ ]--*[0]['d'][^]
*/

Status InitGList(GLNode *L)
{
    L->tag = LIST;
    L->hp = NULL;
    L->tp = NULL;
    return OK;
}

// (a,b,c,(d),(e,(f,g),(h)))
// ((),(e),(a,(b,c,d)))
Status CreateGList(GLNode *L, char *S)
{
    GList curL;
    LNodeStack stack;
    InitLNodeStack(&stack);
    // 1: child of curL, 2: next of curL
    int operation = 1;
    char *p = ++S;
    curL = L;
    PSElemType e = (PSElemType)malloc(sizeof(SElemType));
    e->data = L;
    LNodeStack_Push(&stack, e);
    while (*p != '\0')
    {
        if (*p == '(')
        {
            GLNode *pn = (GLNode *)malloc(sizeof(GLNode));
            pn->tag = LIST;
            pn->hp = NULL;
            pn->tp = NULL;
            if (operation == 1)
            {
                curL->hp = pn;
            }
            else if (operation == 2)
            {
                curL->tp = pn;
            }
            PSElemType e = (PSElemType)malloc(sizeof(SElemType));
            e->data = pn;
            curL = pn;
            LNodeStack_Push(&stack, e);
            operation = 1;
        }
        else if (*p == ',')
        {
            operation = 2;
        }
        else if (*p == ')')
        {
            PSElemType e = LNodeStack_Pop(&stack);
            curL = e->data;
        }
        else
        {
            GLNode *pn = (GLNode *)malloc(sizeof(GLNode));
            pn->tag = ATOM;
            pn->atom = *p;
            pn->tp = NULL;
            if (operation == 1)
            {
                curL->hp = pn;
            }
            else if (operation == 2)
            {
                curL->tp = pn;
            }
            curL = pn;
        }
        p++;
    }
    return OK;
}

void DestroyGList(GList L)
{

    if (L->tp != NULL)
    {
        DestroyGList(L->tp);
    }
    if (L->tag == LIST && L->hp != NULL)
    {
        DestroyGList(L->hp);
    }
    free(L);
}

void GLists_Traverse(GList L)
{
    if (L->tag == LIST)
    {
        printf("(");
        if (L->hp)
        {
            for (GList p = L->hp; p; p = p->tp)
            {
                GLists_Traverse(p);
                if (p->tp)
                {
                    printf(",");
                }
            }
        }
        printf(")");
    }
    if (L->tag == ATOM)
    {
        printf("%c", L->atom);
    }
}

int GListDepth(GList L)
{
    if (!L)
        return 1;
    if (L->tag == ATOM)
        return 0;
    int max = 0;
    for (GList p = L; p != NULL; p = p->tp)
    {
        int depth = GListDepth(p->hp);
        if (depth > max)
            max = depth;
    }
    return max + 1;
}

int GListItem(GList L)
{
    if (L->tag == ATOM)
        return 1;
    int sum = 0;
    for (GList p = L->hp; p; p = p->tp)
    {
        sum += GListItem(p);
    }
    return sum;
}

int GListLength(GList L)
{
    int len = 0;
    for (GList p = L->hp; p; p = p->tp)
    {
        len++;
    }
    return len;
}

Status GListEmpty(GList L)
{
    if (L->tag == ATOM)
        return TRUE;
    if (L->hp)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

GList GetHead(GList L)
{
    if (L->tag == LIST)
    {
        return L->hp;
    }
    else
    {
        return NULL;
    }
}

GList GetTail(GList L)
{
    if (L->tag == LIST)
    {
        GList p = (GList)malloc(sizeof(GLNode));
        p->tag = LIST;
        p->hp = L->hp->tp;
        p->tp = NULL;
        return p;
    }
    else
    {
        return NULL;
    }
}

void CopyGList(GList *T, GList L)
{
    if (!L)
    {
        *T = NULL;
    }
    else
    {
        *T = (GList)malloc(sizeof(GLNode));
        if (L->tag == ATOM)
        {
            (*T)->tag = ATOM;
            (*T)->atom = L->atom;
            CopyGList(&((*T)->tp), L->tp);
        }
        else
        {
            (*T)->tag = LIST;
            CopyGList(&((*T)->tp), L->tp);
            CopyGList(&((*T)->hp), L->hp);
        }
    }
}

void InsertFirst(GList L, GList e)
{
    e->tp = L->hp;
    L->hp = e;
}

void DeleteFirst(GList L, GList *e)
{
    *e = L->hp;
    L->hp = L->hp->tp;
}