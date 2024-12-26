#include <stdio.h>
#include <stdlib.h>

#define MAX_COL 100
#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0

typedef struct {
    short int vert;
    short int horiz;
} offsets;

offsets move = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

typedef struct {
    short int row;
    short int col;
    short int dir; 
} element;

element stack[MAX_STACK_SIZE];
int top;
int maiz[MAX_COL][MAX_COL];

void readMaze(int *row, int *col);
void push(int *top, element val);
element pop(int *top);
int isEmpty(int *top);
void path(int num_row, int num_col, int mark[MAX_COL][MAX_COL]);
int printMaze(int num_row, int num_col);

int main () {
    int row, col;
    readMaze(&row, &col);
    int mark[MAX_COL][MAX_COL];
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            mark[i][j] = 0;
        }
    }
    path(row, col, mark);
    return 0;
}

void path(int num_row, int num_col, int mark[MAX_COL][MAX_COL]) {
    int row, col, next_row, next_col, dir, found = FALSE;
    element position;
    int ent_row, ent_col, exit_row, exit_col;
    scanf("%d %d %d %d", &exit_row, &exit_col, &ent_row, &ent_col);
    exit_row--; exit_col--; ent_row--; ent_col--;

    mark[ent_row][ent_col] = 1;
    maze[ent_row][ent_col] = 2;
    top = -1;
    position.row = ent_row; position.col = ent_col; position.dir = 0;
    push(&top, position);

    while (top > -1 && !found) {
        position = pop(&top);
        row = position.row; col = position.col; dir = position.dir;
        while (dir < 8 && !found) {
            next_row = row + move[dir].vert;
            next_col = col + move[dir].horiz;
            if (next_row == exit_row && next_col == exit_col) {
                found = TRUE;
            }
            else if (next_row >= 0 && next_row < num_row && next_col >= 0 && next_col < num_col && !maze[next_row][next_col] && !mark[next_row][next_col]) {
                mark[next_row][next_col] = TRUE;
                maze[next_row][next_col] = 2;
                position.row = row; position.col = col; position.dir = ++dir;
                push(&top, position);
                
                row = next_row;
                col = next_col;
                dir = 0;
            }
            else {
                dir++;
            }
        }
    }
}