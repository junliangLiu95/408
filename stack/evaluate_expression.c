#include "stack.h"
#include <string.h>
typedef struct SElemType
{
    char val[10];
} SElemType;

char OP[] = {'+', '-', '*', '/', '(', ')', '#'};

char OpPrecedeTable[7][7] = {
    {'>', '>', '<', '<', '<', '>', '>'},
    {'>', '>', '<', '<', '<', '>', '>'},
    {'>', '>', '>', '>', '<', '>', '>'},
    {'>', '>', '>', '>', '<', '>', '>'},
    {'<', '<', '<', '<', '>', '=', '-'},
    {'>', '>', '>', '>', '-', '>', '>'},
    {'<', '<', '<', '<', '<', '-', '='},
};

int Index(char op)
{
    int index = 0;
    while (index < 7)
    {
        if (OP[index] == op)
        {
            return index;
        }
        index++;
    }
    return -1;
}

char GetTop(LNodeStack S)
{
    if (S.top != NULL)
    {
        return S.top->data->val[0];
    }
    else
    {
        return '-';
    }
}

char precede(char theta1, char theta2)
{
    return OpPrecedeTable[Index(theta1)][Index(theta2)];
}

int Operate(char *a, char theta, char *b)
{
    int operand1, operand2;
    sscanf(a, "%d", &operand1);
    sscanf(b, "%d", &operand2);
    switch (theta)
    {
    case '+':
        return operand1 + operand2;
        break;
    case '-':
        return operand1 - operand2;
        break;
    case '*':
        return operand1 * operand2;
        break;
    case '/':
        return operand1 / operand2;
        break;
    default:
        break;
    }
    return 0;
}

/*
    72+9*(4-2)#

    OPTR           OPND          c
    #
    #              72
    # +            72
    # +            72 9
    # + *          72 9
    # + * (        72 9
    # + * (        72 9 4
    # + * ( -      72 9 4
    # + * ( -      72 9 4 2
    # + * (        72 9 6        )
    # + *          72 9 6        #
    # +            72 54         #
    #              126           #
                   126
*/

void EvaluateExpression()
{
    LNodeStack OPTR, OPND;
    InitLNodeStack(&OPTR);
    InitLNodeStack(&OPND);
    PSElemType e = (PSElemType)malloc(sizeof(SElemType));
    strcat(e->val, "#");
    LNodeStack_Push(&OPTR, e);
    printf("enter Expression, end with #\n");
    char c = getchar();
    char tmp[10] = "";
    while (c != '#' || GetTop(OPTR) != '#')
    {
        if (Index(c) == -1)
        {
            int len = strlen(tmp);
            tmp[len++] = c;
            tmp[len] = '\0';
            c = getchar();
        }
        else
        {
            int len = strlen(tmp);

            if (len != 0)
            {
                PSElemType e = (PSElemType)malloc(sizeof(SElemType));
                strcat(e->val, tmp);
                LNodeStack_Push(&OPND, e);
                tmp[0] = '\0';
            }
            switch (precede(GetTop(OPTR), c))
            {
            case '<':
            {
                PSElemType e = (PSElemType)malloc(sizeof(SElemType));
                char tmp = c;
                strcat(e->val, &tmp);
                LNodeStack_Push(&OPTR, e);
                c = getchar();
                break;
            }

            case '=':
                LNodeStack_Pop(&OPTR);
                c = getchar();
                break;
            case '>':
            {
                char *a = LNodeStack_Pop(&OPND)->val;
                char *b = LNodeStack_Pop(&OPND)->val;
                char *theta = LNodeStack_Pop(&OPTR)->val;
                int result = Operate(b, theta[0], a);
                PSElemType e = (PSElemType)malloc(sizeof(SElemType));
                sprintf(e->val, "%d", result);
                LNodeStack_Push(&OPND, e);
                break;
            }
            default:
                break;
            }
        }
    }
    char *result = OPND.top->data->val;
    printf("%s", result);
}

int main()
{
    EvaluateExpression();
    return 0;
}