#include "stack.h"

typedef struct PostType
{
    int x;
    int y;
};
typedef struct SElemType
{
    char data;
} SElemType;

void visit(int p)
{
    printf("%d ", p);
}

void visit_LNodeStack(PSElemType p)
{
    printf("%c", p->data);
}

Status bracketMatch(char str[], int strlen)
{
    LNodeStack stack;
    for (int i = 0; i < strlen; i++)
    {
        if (str[i] == '(' || str[i] == '[')
        {
            PSElemType elem = (PSElemType)malloc(sizeof(PSElemType));
            elem->data = str[i];
            LNodeStack_Push(&stack, elem);
        }
        else
        {
            LNodeStackTraverse(stack, visit_LNodeStack);
            printf("\n");
            PSElemType e = LNodeStack_Pop(&stack);
            printf("%c \n", e->data);
            if ((str[i] == ']' && e->data == '(') || (str[i] == ')' && e->data == '['))
            {
                printf("match wrong bracket");
                return FALSE;
            }
        }
    }
    if (stack.top)
        return FALSE;
    return TRUE;
}

void LineEdit()
{
    LNodeStack S;
    InitLNodeStack(&S);
    printf("Enter your word:\n");
    char c = getchar();
    while (c != EOF)
    {
        SElemType *elem = (SElemType *)malloc(sizeof(SElemType));
        switch (c)
        {
        case '#':
            LNodeStack_Pop(&S);
            break;
        case '@':
            ClearLNodeStack(&S);
            break;
        default:
            elem->data = c;
            LNodeStack_Push(&S, elem);
            break;
        }
        c = getchar();
    }
    LNodeStackTraverse(S, visit_LNodeStack);
}

int main()
{
    // char str[] = "([(())]]";
    // int strlen = sizeof(str) / sizeof(str[0]);
    // Status result = bracketMatch(str, strlen);
    // printf("%d", result);
    LineEdit();
    // SqStack S;
    // int s;
    // LNodeStack S2;
    // PSElemType s2 = (PSElemType)malloc(sizeof(SElemType));
    // PSElemType s3;
    // s2->data = 1;
    // InitStack(&S);
    // Push(&S, 1);
    // StackTraverse(S, visit);
    // Pop(&S, &s);
    // printf("%d\n", s);
    // StackTraverse(S, visit);
    // LNodeStack_Push(&S2, s2);
    // LNodeStackTraverse(S2, visit_LNodeStack);
    // SqStack S3 = converion();
    // StackTraverse(S3, visit);
    return 0;
}