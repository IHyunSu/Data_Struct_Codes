#include <stdio.h>
#include <stdlib.h>

#define MAX_COL 100
#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0

typedef struct {
    short int row;
    short int col;
} element;

element stack[MAX_STACK_SIZE];
int top = -1;
int maze[MAX_COL][MAX_COL];
element pathStack[MAX_STACK_SIZE];
int pathTop = -1;

void readMaze(int *row, int *col);
void push(element val);
element pop();
int isEmpty();
void path(int numRow, int numCol);
void printMaze(int numRow, int numCol);

int main() {
    int row, col;
    readMaze(&row, &col);
    path(row, col);
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

void push(element val) {
    if (top >= MAX_STACK_SIZE - 1) {
        printf("스택 오버플로우 발생\n");
        exit(1);
    }
    stack[++top] = val;
}

int isEmpty() {
    return top < 0;
}

element pop() {
    if (isEmpty()) {
        printf("스택 언더플로우 발생\n");
        exit(1);
    }
    return stack[top--];
}

void path(int numRow, int numCol) {
    int row, col, nextRow, nextCol, found = FALSE;
    int directions[8][2] = {
        {-1, 0}, {0, 1}, {1, 0}, {0, -1},
        {-1, 1}, {1, 1}, {1, -1}, {-1, -1}
    };
    element position;
    int entRow, entCol, exitRow, exitCol;

    // 시작점과 종료점 입력
    printf("입력 (종료 행, 종료 열, 시작 행, 시작 열): ");
    scanf("%d %d %d %d", &exitRow, &exitCol, &entRow, &entCol);

    position.row = entRow - 1; // 0 기반 인덱스
    position.col = entCol - 1; // 0 기반 인덱스


    push(position);
    maze[position.row][position.col] = 2; // 경로 표시
    pathStack[++pathTop] = position;

    while (!(isEmpty()) && !found) {
        position = pop();
        row = position.row;
        col = position.col;

        if (row == exitRow - 1 && col == exitCol - 1) {
            found = TRUE;
            break; // 종료점에 도달
        }

        int moved = FALSE;
        for (int dir = 0; dir < 8; dir++) {
            nextRow = row + directions[dir][0];
            nextCol = col + directions[dir][1];
            if (nextRow >= 0 && nextRow < numRow && nextCol >= 0 && nextCol < numCol && maze[nextRow][nextCol] == 0) {
                maze[nextRow][nextCol] = 2; // 경로 표시
                push((element){nextRow, nextCol});
                pathStack[++pathTop] = (element){nextRow, nextCol};
                moved = TRUE; // 유효한 이동 발생
                break;
            }
        }

        // 이동할 수 없으면 되돌아감
        if (!moved) {
            maze[row][col] = 0; // 경로에서 제외
            pathTop--; // 경로 스택에서 제거
        }
    }

    if (found) {
        // 유효한 경로만 x로 표시
        for (int i = 0; i <= pathTop; i++) {
            maze[pathStack[i].row][pathStack[i].col] = 3; // 'x'로 표시
        }
    } else {
        printf("미로에 경로가 없습니다.\n");
    }

    printMaze(numRow, numCol);
}

void printMaze(int numRow, int numCol) {
    printf("최종 미로:\n");
    for (int i = 0; i < numRow; i++) {
        for (int j = 0; j < numCol; j++) {
            if (maze[i][j] == 3) {
                printf("x ");
            } else {
                printf("%d ", maze[i][j]);
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
            if (maze[i][j] == 3) {
                fprintf(outFile, "x ");
            } else {
                fprintf(outFile, "%d ", maze[i][j]);
            }
        }
        fprintf(outFile, "\n");
    }

    fclose(outFile);
}
