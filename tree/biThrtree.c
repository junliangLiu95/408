#include "biThrtree.h"

void visit(TElemType str)
{
    printf("%c,", str);
}

/*
             1
        2         3
      4    5   6     7
        9
*/

int main()
{
    int index = 0;
    BiThrTree T, Thrt, current, pre, next;
    CreateBiThrTree(&T, &index);
    BiThrTree_InOrder(T, visit);
    printf("\n");
    InOrderThreading(&Thrt, T);
    InOrderThrTreeTraverse(Thrt);
    printf("\n");
    current = T->lchild;
    pre = BiThrTree_InOrderPre(current);
    next = BiThrTree_InOrderNext(current);
    printf("current: %c, pre: %c, next: %c\n", current->data, pre->data, next->data);
    return 0;
}