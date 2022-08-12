#include "Glist.h"

int main()
{
    GLNode GL;
    char *S = "((),(e),(a,(b,c,d)))";
    CreateGList(&GL, S);
}