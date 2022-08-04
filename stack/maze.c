#include "stack.h"

typedef struct PosType
{
    int x;
    int y;
} PosType;

typedef struct SElemType
{
    int ord;
    struct PosType seat;
    int di;
} SElemType;

int maze[10][10] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 1, 1, 1, 0, 1, 0},
    {0, 1, 1, 0, 1, 1, 1, 0, 1, 0},
    {0, 1, 1, 1, 1, 0, 0, 1, 1, 0},
    {0, 1, 0, 0, 0, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 0, 1, 1, 1, 1, 0},
    {0, 1, 0, 1, 1, 1, 0, 1, 1, 0},
    {0, 1, 0, 0, 0, 1, 0, 0, 1, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

void visit(PSElemType p)
{
    printf("%d, %d ", p->seat.x, p->seat.y);
}

Status compare(PSElemType a, PSElemType b)
{
    if (a->seat.x == b->seat.x && a->seat.y == b->seat.y)
    {
        return TRUE;
    }
    return FALSE;
}

// can this position be pass, and had not been through
Status Pass(PosType p, LNodeStack S)
{
    if (maze[p.y][p.x] == 0)
        return FALSE;
    SElemType s;
    s.seat = p;
    Status exist = LNodeStack_exsit(S, &s, compare);
    if (exist == TRUE)
        return FALSE;
    return TRUE;
}

// Print position through
void FootPrint(PosType p)
{
    printf("Into %d,%d\n", p.x, p.y);
}
// return next position of p, by direction di
//          4
//       3  p  1
//          2
PosType NextPos(PosType p, int di)
{
    // PosType next = {p.x, p.y};
    PosType *next = (PosType *)malloc(sizeof(PosType));
    next->x = p.x;
    next->y = p.y;
    switch (di)
    {
    case 1:
        next->x++;
        break;
    case 2:
        next->y++;
        break;
    case 3:
        next->x--;
        break;
    case 4:
        next->y--;
        break;
    default:
        break;
    }
    return *next;
}

// Print position that can't pass
void MarkPrint(PosType p)
{
    printf("block in %d,%d\n", p.x, p.y);
}

void PrintMaze(LNodeStack S)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            SElemType s;
            s.seat.x = j;
            s.seat.y = i;
            if (LNodeStack_exsit(S, &s, compare) == TRUE)
            {
                printf(" *");
            }
            else
            {
                printf(" %d", maze[i][j]);
            }
        }
        printf("\n");
    }
}

Status MazePath(PosType start, PosType end)
{
    LNodeStack S;
    InitLNodeStack(&S);
    PosType curpos = start;
    int curstep = 1;
    do
    {
        if (Pass(curpos, S) == OK)
        {
            FootPrint(curpos);
            SElemType *e = (SElemType *)malloc(sizeof(SElemType));
            e->ord = curstep;
            e->seat = curpos;
            e->di = 1;
            LNodeStack_Push(&S, e);
            if (curpos.x == end.x && curpos.y == end.y)
            {
                PrintMaze(S);
                return TRUE;
            }

            curpos = NextPos(curpos, 1);
            curstep++;
        }
        else
        {
            if (!StackEmpty(S))
            {
                MarkPrint(curpos);
                PSElemType e = LNodeStack_Pop(&S);
                LNodeStackTraverse(S, visit);
                while (e->di == 4 && !StackEmpty(S))
                {

                    e = LNodeStack_Pop(&S);
                    MarkPrint(e->seat);
                }
                if (e->di < 4)
                {
                    e->di++;
                    LNodeStack_Push(&S, e);
                    curpos = NextPos(e->seat, e->di);
                }
            }
        }
    } while (!StackEmpty(S));
    return FALSE;
}

int main()
{
    PosType start = {1, 1};
    PosType end = {8, 8};
    MazePath(start, end);
}