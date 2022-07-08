#include <stdio.h>
#include <stdlib.h>
#include "LNode_plus.h"

typedef struct ElemType
{
    float coef;
    int expn;
} term, ElemType;

typedef LinkList polynomial;

int cmp(PElemType a, PElemType b)
{
    if (a->expn == b->expn)
        return 0;
    if (a->expn > b->expn)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

void CreatePolyn(polynomial *p, int m)
{
    InitList(p);
    for (int i = 0; i < m; i++)
    {
        PElemType newp = (PElemType)malloc(sizeof(ElemType));
        printf("input coef \n");
        scanf("%f", &newp->coef);
        printf("input expn \n");
        scanf("%d", &newp->expn);
        Link newL = MakeNode(newp);
        Append(p, newL);
    }
}

void DestroyPolyn(polynomial *p)
{
    free(p);
}

void PrintPolyn(polynomial p)
{
    printf("y = ");
    Link l = p.head->next;
    float coef = l->data->coef;
    int expn = l->data->expn;
    if (expn == 1)
    {
        printf("%.2fx", coef);
    }
    else
    {
        printf("%.2fx^%d", coef, expn);
    }
    while (l->next != NULL)
    {
        float coef = l->next->data->coef;
        int expn = l->next->data->expn;
        if (coef > 0)
        {
            if (expn == 1)
            {
                printf("+%.2fx", coef);
            }
            else
            {
                printf("+%.2fx^%d", coef, expn);
            }
        }
        else
        {
            if (expn == 1)
            {
                printf("%.2fx", coef);
            }
            else
            {
                printf("%.2fx^%d", coef, expn);
            }
        }
        l = l->next;
    }
    printf("\n");
}

/*                  la
    A -> {head} -> {1,1} -> {-1,3} -> {3,6} -> NULL
                    lb
    B -> {head} -> {-1,2} ->{-2,4} -> {4,6} -> {5,8} -> NULL

    A ADD B
                            la
    A -> {head} -> {1,1} -> {-1,3} -> {3,6} -> NULL
                    lb
    B -> {head} -> {-1,2} ->{-2,4} -> {4,6} -> {5,8} -> NULL
                                       la
    A -> {head} -> {1,1} -> {-1,2} -> {-1,3} -> {3,6} -> NULL
                    lb
    B -> {head} -> {-2,4} -> {4,6} -> {5,8} -> NULL
*/

void AddPolyn(polynomial *A, polynomial *B)
{
    printf("into AddPolyn");
    Link la = A->head->next;
    printf("la %d", la->data->expn);
    Link lb = B->head->next;
    printf("lb %d", lb->data->expn);
    while (la && lb)
    {
        Link lc;
        float sum;
        switch (cmp(la->data, lb->data))
        {
        case -1:
            printf("into -1\n");
            la = la->next;
            break;
        case 1:
            printf("into 1\n");
            lc = lb;
            lb = lb->next;
            printf("Before ins\n");
            InsBefore(A, la, lc);
            printf("After ins Before\n");
            break;
        case 0:
            printf("into 0\n");
            sum = la->data->coef + lb->data->coef;
            if (sum != 0.0)
            {
                printf("into 0.0\n");
                la->data->coef = sum;
                Position pc = lb;
                lb = lb->next;
                la = la->next;
                printf("Before Del\n");
                Delete(B, pc);
                printf("After Del\n");
            }
            else
            {
                printf("into 0 else\n");
                Position pc = la;
                Position pd = lb;
                lb = lb->next;
                la = la->next;
                printf("Before Del\n");
                Delete(A, pc);
                printf("After Del\n");
                printf("Before Del\n");
                Delete(B, pd);
                printf("After Del\n");
            }
            break;
        }
    }
    if (lb)
    {
        Append(A, lb);
    }
    FreeNode(B->head);
}

int main()
{
    polynomial A;
    polynomial B;
    CreatePolyn(&A, 1);
    PrintPolyn(A);
    CreatePolyn(&B, 2);
    PrintPolyn(B);
    AddPolyn(&A, &B);
    PrintPolyn(A);
    return 0;
}