#include <stdio.h>
#include <stdlib.h>
#include "LNode_plus.h"

typedef struct ElemType
{
    int data;
} ElemType;

void visit(PElemType p)
{
    printf("%d ", p->data);
}

Status compare(PElemType a, PElemType b)
{
    return a->data == b->data ? TRUE : FALSE;
}

int main()
{
    LinkList L;
    LinkList L2;
    InitList(&L);
    InitList(&L2);
    for (int i = 0; i < 5; i++)
    {
        PElemType PE = (PElemType)malloc(sizeof(ElemType));
        PElemType PE2 = (PElemType)malloc(sizeof(ElemType));
        PE->data = i + 1;
        PE2->data = i + 5;
        Link p = MakeNode(PE);
        Link p2 = MakeNode(PE2);
        Append(&L, p);
        Append(&L2, p2);
    }
    printf("Origin LinkList:\n");
    ListTraverse(L, visit);
    PElemType PE1 = (PElemType)malloc(sizeof(ElemType));
    PE1->data = 8;
    Link p1 = MakeNode(PE1);
    InsFirst(&L, L.head, p1);
    printf("Insert 8 as first LNode:\n");
    ListTraverse(L, visit);
    printf("Delete first LNode:\n");
    DelFirst(&L, L.head);
    ListTraverse(L, visit);
    Link p2;
    Remove(&L, &p2);
    printf("remove last LNode, item val = %d\n", p2->data->data);
    ListTraverse(L, visit);
    Link p3;
    LocatePos(L, 2, &p3);
    printf("Locate 2nd LNode value = %d\n", p3->data->data);
    Position p4 = PriorPos(L, p3);
    printf("2nd LNode's prior LNode's value = %d\n", p4->data->data);
    PElemType PE2 = (PElemType)malloc(sizeof(ElemType));
    PE2->data = 8;
    Link p5 = MakeNode(PE2);
    InsBefore(&L, p3, p5);
    printf("Insert 8 before 2nd LNode:\n");
    ListTraverse(L, visit);
    PElemType PE3 = (PElemType)malloc(sizeof(ElemType));
    PE3->data = 8;
    Link p6 = MakeNode(PE3);
    printf("Insert 8 after 2nd LNode:\n");
    InsAfter(&L, p3, p6);
    ListTraverse(L, visit);
    PElemType PE4 = (PElemType)malloc(sizeof(ElemType));
    PE4->data = 8;
    Position p7 = LocateElem(L, PE4, compare);
    printf("Locate value 8 Link's val = %d\n", p7->data->data);
    Link L2_1st = L2.head->next;
    printf("L tail %d\n", L.tail->data->data);
    printf("L2_1st %d\n", L2_1st->data->data);
    printf("L:\n");
    ListTraverse(L, visit);
    printf("L2:\n");
    ListTraverse(L2, visit);
    printf("L append L2:\n");
    Append(&L, L2_1st);
    ListTraverse(L, visit);
    return 0;
}