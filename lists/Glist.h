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
    GLNode data;
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
         *[1][^][ ]--*B[1][ ][^] ---------*C[1][ ][^]
                           |                    |
                           *[0]['e'][^]         *[0]['a'][ ]--*[1][ ][^]
                                                                   |
                                                                   *[0]['b'][ ]--*[0]['c'][ ]--*[0]['d'][^]
*/

Status InitGList(GLNode *L)
{
    L->tag = ATOM;
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
    int operation = 0;
    PSElemType e = (PSElemType)malloc(sizeof(SElemType));
    e->data.tag = LIST;
    e->data.hp = NULL;
    e->data.tp = NULL;
    curL = &e->data;
    LNodeStack_Push(&stack, e);
    char *p = S;
    while (*p != '\0')
    {
        printf("%c", *p);
        p++;
    }
    return OK;
}