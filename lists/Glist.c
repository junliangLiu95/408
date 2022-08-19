#include "Glist.h"

int main()
{
    GList GL = (GList)malloc(sizeof(GLNode));
    InitGList(GL);
    char *S = "((),(e),(a,(b,c,d)))";
    CreateGList(GL, S);
    GLists_Traverse(GL);
    int depth = GListDepth(GL);
    printf("\n depth %d\n", depth);
    int items = GListItem(GL);
    printf("items count %d\n", items);
    int length = GListLength(GL);
    printf("length %d\n", length);
    printf("HEAD of GL:\n");
    GLists_Traverse(GetHead(GL));
    printf("\n TAIL of GL:\n");
    GLists_Traverse(GetTail(GL));
    GList T;
    CopyGList(&T, GL);
    printf("\n copy of GL:\n");
    GLists_Traverse(T);
    GList insertE = (GList)malloc(sizeof(GLNode));
    insertE->tag = ATOM;
    insertE->atom = 'h';
    insertE->tp = NULL;
    InsertFirst(GL, insertE);
    printf("\n insert h as first element into GL:\n");
    GLists_Traverse(GL);
    GList deleteE;
    DeleteFirst(GL, &deleteE);
    printf("\nDelete first element of GL\n");
    GLists_Traverse(GL);
    printf("\nDeleted element\n");
    GLists_Traverse(deleteE);
    DestroyGList(GL);
    DestroyGList(T);
}