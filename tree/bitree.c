#include "bitree.h"

Status visit(TElemType e)
{
    printf("%c,", e);
    return OK;
}

int main()
{
    int index = 0;
    BiTree T = (BiTree)malloc(sizeof(BiTNode));
    CreateBiTree(&T, &index);
    printf("create tree ok\n");
    printf("PreOrder tree \n");
    PreOrderTraverse(T, visit);
    printf("\nInOrder tree \n");
    InOrderTraverse(T, visit);
    printf("\nLevelOrder tree \n");
    LevelOrderTraverse(T, visit);
    return 0;
}