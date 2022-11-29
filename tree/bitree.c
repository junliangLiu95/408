#include "bitree.h"

void visit(TElemType e)
{
    printf("%c,", e);
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
    printf("\nPostOrder tree \n");
    PostOrderTraverse(T, visit);
    printf("\nLevelOrder tree \n");
    LevelOrderTraverse(T, visit);
    printf("\nPreOrder tree without recursion\n");
    preOrderTraverseNonRecur(T, visit);
    printf("\nInOrder tree without recursion\n");
    inOrderTraverseNonRecur(T, visit);
    printf("\nPostOrder tree without recursion\n");
    postOrderTraverseNonRecur(T, visit);
    return 0;
}