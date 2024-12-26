#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_COL 100
#define TRUE 1
#define FALSE 0

typedef struct {
    int row;
    int col;
} element;

int maze[MAX_COL][MAX_COL];
element stack[MAX_STACK_SIZE];
int top = -1; // 스택 초기화

void readMaze(int *row, int *col);
void push(element val);
element pop();
int isEmpty();
void path(int ExitRow, int ExitCol, int numRow, int numCol);

int main() {
    int row, col;
    readMaze(&row, &col);
    path(row - 1, col - 1, row, col); // ExitRow, ExitCol 계산
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
        printf("스택이 가득 찼습니다.\n");
        exit(1); // 프로그램 종료
    }
    stack[++top] = val;
}

element pop() {
    if (isEmpty()) {
        printf("스택이 비어 있습니다.\n");
        exit(1); // 프로그램 종료
    }
    return stack[top--];
}

int isEmpty() {
    return top < 0;
}

void path(int ExitRow, int ExitCol, int numRow, int numCol) {
    int row, col, nextRow, nextCol, found = FALSE;
    int directions[8][2] = {
        {-1, 0}, {0, 1}, {1, 0}, {0, -1},  // N, E, S, W
        {-1, 1}, {1, 1}, {1, -1}, {-1, -1} // NE, SE, SW, NW
    };
    element position;

    // 시작점 초기화 // 여기가 entrance
    position.row = 0;
    position.col = 0;
    push(position);
    maze[position.row][position.col] = 2; // 경로 표시

    // 경로를 저장하기 위한 배열
    element pathStack[MAX_STACK_SIZE];
    int pathTop = -1;
    pathStack[++pathTop] = position;

    while (!isEmpty() && !found) {
        position = pop();
        row = position.row;
        col = position.col;

        // 도착점 체크
        if (row == ExitRow && col == ExitCol) {
            found = TRUE;
            break;
        }

        // 다음 위치 탐색
        for (int dir = 0; dir < 8 && !found; dir++) {
            nextRow = row + directions[dir][0];
            nextCol = col + directions[dir][1];

            // 경계 및 이동 가능성 검사
            if (nextRow >= 0 && nextRow < numRow && nextCol >= 0 && nextCol < numCol && maze[nextRow][nextCol] == 0) {
                maze[nextRow][nextCol] = 2; // 경로 표시
                push((element){nextRow, nextCol}); // 스택에 추가
                pathStack[++pathTop] = (element){nextRow, nextCol}; // 경로 저장
            }
        }
    }

    // 경로 찾기 결과 출력
    if (found) {
        printf("The path is:\n");
        printf("row col\n");
        for (int i = 0; i < pathTop; i++) {
            printf("%2d %5d\n", pathStack[i].row + 1, pathStack[i].col + 1); // 1 기반 인덱스 출력
        }
    } else {
        printf("The maze does not have a path.\n");
    }
}
