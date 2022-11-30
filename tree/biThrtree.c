#include "biThrtree.h"

void visit(TElemType str)
{
    printf("%c,", str);
}

int main()
{
    int index = 0;
    BiThrTree T;
    CreateBiThrTree(&T, &index);
    BiThrTree_PreOrder(T, visit);
    return 0;
}