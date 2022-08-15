#include "Glist.h"

int main()
{
    GLNode GL;
    InitGList(&GL);
    char *S = "((),(e),(a,(b,c,d)))";
    CreateGList(&GL, S);
    GLists_Traverse(&GL, 1);
}