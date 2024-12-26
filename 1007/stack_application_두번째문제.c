#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define FALSE 0
#define TRUE 1
#define MAX_COL 100

typedef struct {
    int vert;
    int horiz;
} offsets;

offsets move[8] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {-1, -1}, {1, -1}, {1, 1}, {-1, 1}};

typedef struct {
    short int row;
    short int col;
    short int dir;
} element;

element stack[MAX_STACK_SIZE];

void readMaze(int *row, int *col);
void path(int numRow, int numCol, int mark[MAX_COL][MAX_COL]);
void push(int *top, element position);
element pop(int *top);
void printMaze(int numRow, int numCol);

int top;
int maze[MAX_COL][MAX_COL];

int main() {
    int row, col;
    int mark[MAX_COL][MAX_COL];
    readMaze(&row, &col);
    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            mark[i][j] = 0; // 초기화
        }
    }
    
    path(row, col, mark);
    return 0;
}

void readMaze(int *row, int *col) {
    FILE *file;
    if ((file = fopen("in.txt", "r")) == NULL) {
        printf("파일을 열 수 없습니다.\n");
        exit(1);
    }
    fscanf(file, "%d %d", row, col);

    for (int i = 0; i < *row; i++) {
        for (int j = 0; j < *col; j++) {
            fscanf(file, "%d", &maze[i][j]);
        }
    }
    fclose(file);
}

void path(int numRow, int numCol, int mark[MAX_COL][MAX_COL]) {
    int row, col, next_row, next_col, dir;
    int found = FALSE;
    element position;
    int entRow, entCol, exit_row, exit_col;

    // 시작점과 종료점 입력
    scanf("%d %d %d %d", &exit_row, &exit_col, &entRow, &entCol);
    
    // 0 기반 인덱스 변환
    exit_row--; exit_col--; entRow--; entCol--;
    
    mark[entRow][entCol] = 1; // 시작점 마킹
    top = -1; // 스택 초기화
    position.row = entRow; position.col = entCol; position.dir = 0; // 시작점 설정
    push(&top, position); // 시작점 스택에 추가

    while (top > -1 && !found) {
        position = pop(&top);
        row = position.row; col = position.col; dir = position.dir;

        while (dir < 8 && !found) {
            next_row = row + move[dir].vert;
            next_col = col + move[dir].horiz;

            // 종료점에 도달했는지 확인
            if (next_row == exit_row && next_col == exit_col) {
                found = TRUE;
            } 
            // 유효한 이동 확인
            else if (next_row >= 0 && next_row < numRow && next_col >= 0 && next_col < numCol && !maze[next_row][next_col] && !mark[next_row][next_col]) {
                mark[next_row][next_col] = TRUE; // 경로 마킹
                maze[next_row][next_col] = 2;
                position.row = row; position.col = col; position.dir = ++dir; // 현재 위치와 방향 저장
                push(&top, position); // 이전 위치를 스택에 저장
                
                // 이동
                row = next_row;
                col = next_col;
                dir = 0; // 새로운 방향으로 리셋
            } 
            else {
                dir++; // 다음 방향으로 이동
            }
        }
    }

    if (found) {
        maze[entRow][entCol] = 2; // 시작점 표시
        maze[exit_row][exit_col] = 2; // 종료점 표시
        printMaze(numRow, numCol);
    } else {
        printf("미로에 경로가 없습니다.\n");
    }
}

void printMaze(int numRow, int numCol) {
    printf("최종 미로:\n");
    for (int i = 0; i < numRow; i++) {
        for (int j = 0; j < numCol; j++) {
            if (maze[i][j] == 2) {
                printf("x "); // 경로 표시
            } else {
                printf("%d ", maze[i][j]); // 벽 또는 통로 표시
            }
        }
        printf("\n");
    }

    // 결과를 out.txt 파일에 저장
    FILE *outFile = fopen("out.txt", "w");
    if (outFile == NULL) {
        printf("out.txt 파일을 열 수 없습니다.\n");
        exit(1);
    }

    for (int i = 0; i < numRow; i++) {
        for (int j = 0; j < numCol; j++) {
            if (maze[i][j] == 2) {
                fprintf(outFile, "x "); // 경로 표시
            } else {
                fprintf(outFile, "%d ", maze[i][j]); // 벽 또는 통로 표시
            }
        }
        fprintf(outFile, "\n");
    }

    fclose(outFile);
}

void push(int *top, element position) {
    (*top)++;
    stack[*top] = position;
}

element pop(int *top) {
    element result;
    if (*top < 0) {
        printf("스택이 비었습니다.\n");
        exit(1);
    } else {
        result = stack[*top];
        (*top)--;
    }
    return result;
}
