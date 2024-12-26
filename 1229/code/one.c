//
// Program (BST vs Hashing)
// Base Setting
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning (disable:4996)

#define MALLOC(p,s) \
    if ((p = malloc(s)) == NULL) { \
        fprintf(stderr, "Insufficient Memory"); \
        exit(EXIT_FAILURE); \
    }

#define MAX_STRING_LENGTH 256

//
// Binary Tree struct
//

typedef struct {
    char key[MAX_STRING_LENGTH];
} element;

typedef struct tree {
    element data;
    struct tree* leftChild;
    struct tree* rightChild;
} tree, *treePointer;

treePointer root = NULL; /* init of root node */

//
// Hash table struct
//

typedef struct node {
    int key; /* <- (transration) char -> int */
    char value[MAX_STRING_LENGTH]; /* <- char data */
    struct node* next; /* <- Chain for linked list */
} node, *nodePointer;

typedef struct {
    struct node* head; /* <- Start Point of bucket */
    int count; /* Bucket number counting */
} bucket;

bucket* hashTable = NULL;
#define BUCKET_SIZE 100001 /* Bucket의 최대 값 */


//
// Count for BST and Hash
//

int BST_n = 0; /* <- BST에 저장된 데이터 개수를 Counting 하는 전역 변수 */
int Hash_n = 0; /* <- Hash Table에 저장된 데이터 개수를 COunting 하는 전역 변수 */

//
// Counting words (BST_n과 Hash_n과 같은 의미이지만, 다른 목적에서 사용될 전역 변수들)
//

int words_n = 0;  /* <- BST에 저장된 단어들의 개수를 세는 전역 변수 */
int words2_n = 0; /* <- Hash Table에 저장된 단어들의 개수를 세는 전역 변수 */


//
// Menu function
//

void menu();
void insert_result(char fname[]); /* BST와 Hash의 삼입 결과를 파일을 생성하고 저장하는 함수 */
void insert_result_display(char fname[]); /* BST와 Hash의 삼입 결과를 저장한 파일을 입력받으면 출력하는 함수 */
void search_result(char fname[]); /* BST와 Hash의 검색 결과를 파일을 생성하고 저장하는 함수 */
void search_result_display(char fname[]); /* BST와 Hash의 검색 결과를 저장한 파일을 입력받으면 출력하는 함수 */


//
// BST realization functions
//

int bst_settings(char fname[]);

treePointer modifiedSearch(treePointer node, char k[]);
int insertBST(treePointer* node, char k[]);
double bst_insert_result(char fname[]);
double bst_search_result(char fname[]);
void freeBST(treePointer node);

void inorder(treePointer node); /* test용 출력 */

//
// HASH TABLE
//

int hash_settings(char fname[]); 

unsigned int stringToInt(char *key); /* (char -> int) function*/
nodePointer createNode(int key, char* value);
int hashFunction(int key);
int add(int key, char* value);
int search(int key);
double hash_insert_result(char fname[]);
double hash_search_result(char fname[]);
void freeHashTable();

void display(); /* test용 출력 */


//
// Main function
//


int main () {
    menu();

    freeBST(root);
    freeHashTable();

    return 0;
}





/*  BST and Hashing Menu
    1. 사전 구성
    2. 단어 삼입
    3. 단어 검색
    4. 삼입 성능 비교 (BST vs 해싱)
    5. 검색 성능 비교 (BST vs 해싱)
    6. 종료                     */

void menu() {

    //
    // 사전 설정
    //

    for (int i = 0; i < 39; i++) printf("=");

    printf("\n");
    printf("   BST-Hashing 성능 비교\n");

    for (int i = 0; i < 39; i++) printf("=");
    int select;

    //
    // 메뉴 시작 (6 입력 시 종료)
    //

    while (1) {

        printf("\n1. 사전 구성\n2. 단어 삽입\n3. 단어 검색\n4. 삼입 성능 비교 (BST vs 해싱)\n5. 검색 성능 비교 (BST vs 해싱)\n6. 종료\n");

        for (int i = 0; i < 39; i++) printf("-");
        printf("\n선택: ");
        scanf("%d", &select);

        //
        // 1번 == 사전 구성
        //

        if (select == 1) {
            char fname[20];

            printf("파일 이름을 입력하세요: ");
            scanf("%s", fname);

            int test1 = bst_settings(fname);
            int test2 = hash_settings(fname);

            if (test1 && test2) /* test1, test2 모두 1일 시 조건 실행 */
                printf("\nBST와 해시 테이블에 삼입 완료\n");

            select = 0; /* 초기화 */
        }

        //
        // 2번 == 단어 삼입
        //

        else if (select == 2) {
            char temp[MAX_STRING_LENGTH];

            printf("단어를 입력하세요: ");
            scanf("%s", temp);

            int test1 = insertBST(&root, temp); // BST

            int tmp_key = stringToInt(temp); // Hash
            int test2 = add(tmp_key, temp);

            /* 조건에 맞추어 실행 결과 출력 */
            if (test1 && test2)
                printf("\n- BST: S\n- Hash: S\n");
            else if (test1 == 1 && test2 == 0)
                printf("\n- BST: S\n- Hash: N\n");
            else if (test1 == 0 && test2 == 1)
                printf("\n- BST: N\n- Hash: S\n");
            else
                printf("\n- BST: N\n- Hash: N\n");
            
            select = 0; // 초기화
        }

        //
        // 3번 == 단어 검색
        //

        else if (select == 3) {
            char temp[MAX_STRING_LENGTH];

            printf("단어를 입력하세요: ");
            scanf("%s", temp);

            modifiedSearch(root, temp); /* BST search */
            int tmp_key = stringToInt(temp); /* Hash search (index return 받기) */
            int Hash_index = search(tmp_key);

            printf("\n- BST: S (비교 %d회)\n- Hash: S (인덱스 %d, 비교 %d회)\n", BST_n, Hash_index, Hash_n);

            BST_n = 0, Hash_n = 0;

            select = 0; /* 초기화 */
        }

        //
        // 4번 == 삼입 성능 비교
        //

        else if (select == 4) {
            char temp[MAX_STRING_LENGTH];

            printf("파일 이름을 입력하세요 : ");
            scanf("%s", temp);
            insert_result(temp);

            printf("\n파일 이름(삼입결과 출력)을 입력하세요: ");
            scanf("%s", temp);
            insert_result_display(temp);

            select = 0; /* 초기화 */
        }

        //
        // 5번 == 검색 성능 비교
        //

        else if (select == 5) {

            char temp[MAX_STRING_LENGTH];

            printf("파일 이름을 입력하세요 : ");
            scanf("%s", temp);
            search_result(temp);

            printf("\n파일 이름(검색결과 출력)을 입력하세요: ");
            scanf("%s", temp);
            search_result_display(temp);

            select = 0; /* 초기화 */

        }

        //
        // 6번 == 종료
        //

        else if (select == 6) {
            break;
        }

        // test용
        // 7 - BST
        // 8 - Hash

        // else if (select == 7) {
        //     inorder(root);
        //     select = 0;
        // }
        // else if (select == 8) {
        //     display();
        //     select = 0;
        // }
    }
}





//
// BST Functions
//

int bst_settings(char fname[]) {

    FILE* file;
    if ((file = fopen(fname, "r")) == NULL) {
        printf("can not open file\n");
        return 0;
    }
    
    char temp[MAX_STRING_LENGTH]; // Insert Bst function 활용
    while ((fscanf(file, "%s", temp)) == 1) {
        insertBST(&root, temp);
    }
    fclose(file);
    return 1;
}

//
// 입력된 단어가 있는지 없는지 찾는 함수
//

treePointer modifiedSearch(treePointer node, char k[]) {
    while (node) {
        BST_n++;
        if (strcmp(node->data.key, k) == 0) return node;
        if (strcmp(node->data.key, k) == 1) node = node->leftChild;
        else node = node->rightChild;
    }
    return NULL;
}

//
// 입력된 단어가 없는 경우 BST에 insert
//

int insertBST(treePointer* node, char k[]) {
    treePointer ptr = NULL, temp = modifiedSearch(*node, k);
    BST_n = 0; /* BST에 저장된 데이터의 개수를 Counting */

    if (!temp) {
        MALLOC(ptr, sizeof(*ptr));
        strcpy(ptr->data.key, k);
        ptr->leftChild = NULL, ptr->rightChild = NULL;

        if (!(*node)) {
            *node = ptr;
        }
        else {
            treePointer current = *node, parent = NULL;
            while (current != NULL) {
                parent = current;
                if (strcmp(current->data.key, k) > 0)
                    current = current->leftChild;
                else    
                    current = current->rightChild;
            }

            if (strcmp(parent->data.key, k) > 0)
                parent->leftChild = ptr;
            else
                parent->rightChild = ptr;
        }
        return 1;
    }
    return 0;
}

//
// Test용 (BST display)
//

void inorder(treePointer node) {
    if (node) {
        inorder(node->leftChild);
        printf("%s\n", node->data.key);
        inorder(node->rightChild);
    }
}



//
// HASHING
//


int hash_settings(char fname[]) {
    if (hashTable) {
        freeHashTable();
    }

    MALLOC(hashTable, sizeof(bucket) * BUCKET_SIZE);
    FILE *file;
    if ((file = fopen(fname, "r")) == NULL) {
        printf("can not open file");
        return 0;
    }
    for(int i = 0; i < BUCKET_SIZE; i++) {
        hashTable[i].head = NULL;
        hashTable[i].count = 0;
    }

    char temp_string[MAX_STRING_LENGTH];
    int temp_key;
    while ((fscanf(file, "%s", temp_string)) == 1) {
        temp_key = stringToInt(temp_string); // 변환 후 Insert
        add(temp_key, temp_string);
    }
    fclose(file);
    return 1;
}

//
// 입력된 문자열을 int형으로 변환
//

unsigned int stringToInt(char *key) {
    int number = 0;
    while (*key)    
        number += *key++;
    return number;
}

//
// Chaning
//

nodePointer createNode(int key, char* value) {
    nodePointer newNode;
    MALLOC(newNode, sizeof(node));
    if (!newNode) {
        return NULL;
    }
    newNode->key = key;
    strcpy(newNode->value, value);
    newNode->next = NULL;

    return newNode;
}

//
// 최대 수 만큼
//

int hashFunction(int key) {
    return key%BUCKET_SIZE;
}

//
// Hash table insert
//

int add(int key, char* value) {
    int hashIndex = hashFunction(key);
    nodePointer newNode = createNode(key, value);
    // 계산한 인덱스의 버켓에 아무 노드도 없을 경우
    if (hashTable[hashIndex].count == 0){
        hashTable[hashIndex].count = 1;
        hashTable[hashIndex].head = newNode; // head를 교체
    }
    // 버켓에 다른 노드가 있을 경우 한칸씩 밀고 내가 헤드가 된다(실제로는 포인터만 바꿔줌)
    else{
        newNode->next = hashTable[hashIndex].head;
        hashTable[hashIndex].head = newNode;
        hashTable[hashIndex].count++;
    }
    return 1;
}

//
// Hash search
//

int search(int key) {
    int hashIndex = hashFunction(key);
    struct node* node = hashTable[hashIndex].head;
    int flag = 0;
    while (node != NULL)
    {
        if (node->key == key){
            flag = 1;
            break;
        }
        node = node->next;
    }
    if (flag == 1){ // 키를 찾았다면
        Hash_n++;
        return node->key; // Index return
    }
    else{
        return 0;
    }
}

//
// Test용 (Hash display)
//

void display() {
    // 반복자 선언
    nodePointer iterator;
    printf("\n========= display start ========= \n");
    for (int i = 0; i<BUCKET_SIZE; i++){
        iterator = hashTable[i].head;
        printf("Bucket[%d] : ", i);
        while (iterator != NULL)
        {
            printf("(key : %d, val : %s)  -> ", iterator->key, iterator->value);
            iterator = iterator->next;
        }
        printf("\n");
    }
    printf("\n========= display complete ========= \n");
}



//
// 삼입 성능 비교
//

void insert_result(char fname[]) {

    double bst_result = bst_insert_result(fname);
    double hash_result = hash_insert_result(fname);

    char filename[MAX_STRING_LENGTH];
    char *dot = strrchr(fname, '.');
    if (dot != NULL) *dot = '\0';
    sprintf(filename, "%sResult.txt", fname);
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "can not open file\n");
        return;
    }

    fprintf(file, "%d\n", words_n);
    fprintf(file, "%f\n", bst_result);
    fprintf(file, "%f\n", hash_result);

    fclose(file);

    words_n = 0; // 초기화
}

void insert_result_display(char fname[]) {

    FILE *file = fopen(fname, "r");
    if (file == NULL) {
        fprintf(stderr, "can not open file\n");
        return;
    }

    int n;
    double BST, HASHING;

    fscanf(file, "%d", &n);
    fscanf(file, "%lf", &BST);
    fscanf(file, "%lf", &HASHING);

    fclose(file);

    printf("\n[삼입 성능]\n");
    printf("데이터 개수 | BST          | 해싱\n");
    printf("---------------------------------\n");
    printf("%d       | %.2f ms      | %.2f ms\n", n, BST, HASHING);
    printf("\n");

    return;
}

//
// BST insert
//

double bst_insert_result(char fname[]) {

    FILE* file;
    if ((file = fopen(fname, "r")) == NULL) {
        printf("can not open file\n");
        return 0;
    }
    
    char temp[MAX_STRING_LENGTH]; // Insert Bst function 활용

    // BST clock check
    clock_t start_bst, end_bst;
    start_bst = clock();
    while ((fscanf(file, "%s", temp)) == 1) {
        insertBST(&root, temp);
        words_n++;
        // if (words_n == 50000)
        //     break;
    }
    end_bst = clock();
    fclose(file);

    double bst_result = ((double)(end_bst - start_bst)) / (CLOCKS_PER_SEC / (float)words_n);
    return bst_result;

}

//
// Hash insert
//

double hash_insert_result(char fname[]) {

    MALLOC(hashTable, sizeof(bucket) * BUCKET_SIZE);
    FILE *file;
    if ((file = fopen(fname, "r")) == NULL) {
        printf("can not open file");
        exit(1);
    }
    char temp_string[50];

    // hash clock check
    clock_t start_hash, end_hash;
    int temp_key;
    start_hash = clock();
    while ((fscanf(file, "%s", temp_string)) == 1) {
        temp_key = stringToInt(temp_string); // 변환 후 Insert
        add(temp_key, temp_string);
        words2_n++;
        // if (words2_n == 50000)
        //     break;
    }
    end_hash = clock();
    fclose(file);

    double hash_result = ((double)(end_hash - start_hash)) / (CLOCKS_PER_SEC / (float)words_n);
    return hash_result;

}

//
// 검색 성능 비교
//

void search_result(char fname[]) {
    double bst_result = bst_search_result(fname);
    double hash_result = hash_search_result(fname);

    char filename[MAX_STRING_LENGTH];
    char *dot = strrchr(fname, '.');
    if (dot != NULL) *dot = '\0';
    sprintf(filename, "%sResult.txt", fname);
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "can not open file\n");
        return;
    }

    fprintf(file, "%d\n", words_n);
    fprintf(file, "%f\n", bst_result);
    fprintf(file, "%f\n", hash_result);

    fclose(file);

    words_n = 0; // 초기화
    words2_n = 0;
}

void search_result_display(char fname[]) {
    FILE *file = fopen(fname, "r");
    if (file == NULL) {
        fprintf(stderr, "can not open file\n");
        return;
    }

    int n;
    double BST, HASHING;

    fscanf(file, "%d", &n);
    fscanf(file, "%lf", &BST);
    fscanf(file, "%lf", &HASHING);

    fclose(file);

    printf("\n[검색 성능]\n");
    printf("데이터 개수 | BST          | 해싱\n");
    printf("---------------------------------\n");
    printf("%d       | %.2f ms      | %.2f ms\n", n, BST, HASHING);
    printf("\n");

    return;
}

//
// BST search
//

double bst_search_result(char fname[]) {
    FILE* file;
    if ((file = fopen(fname, "r")) == NULL) {
        printf("can not open file\n");
        return 0;
    }
    
    char temp[MAX_STRING_LENGTH]; // Search bst function 활용

    int temp_n = 1;
    int temp_words_index;

    // Bst clock check
    clock_t start_bst, end_bst;
    start_bst = clock();
    while ((fscanf(file, "%s", temp)) == 1) {
        treePointer temp1 = modifiedSearch(root, temp);
        words_n++;
        // if (words_n == 100000)
        //     break;
    }
    end_bst = clock();
    fclose(file);

    double bst_result = ((double)(end_bst - start_bst)) / (CLOCKS_PER_SEC / (float)words_n);
    return bst_result;
}

//
// Hash search
//

double hash_search_result(char fname[]) {

    FILE *file;
    if ((file = fopen(fname, "r")) == NULL) {
        printf("can not open file");
        exit(1);
    }
    char temp_string[MAX_STRING_LENGTH];

    int result_index = 0;

    // hash clock check
    clock_t start_hash, end_hash;
    int temp_key;
    start_hash = clock();
    while ((fscanf(file, "%s", temp_string)) == 1) {
        result_index = temp_key = stringToInt(temp_string); // 변환 후 Insert
        search(temp_key);
        words2_n++;
        // if (words2_n == 100000)
        //     break;
    }
    end_hash = clock();
    fclose(file);

    double hash_result = ((double)(end_hash - start_hash)) / (CLOCKS_PER_SEC / (float)words_n);
    return hash_result;

}

//
//메모리 해제 함수
//

void freeBST(treePointer node) {
    if (node) {
        freeBST(node->leftChild);
        freeBST(node->rightChild);
        free(node);
    }
}

void freeHashTable() {
    if (hashTable) {
        for (int i = 0; i < BUCKET_SIZE; i++) {
            nodePointer current = hashTable[i].head;
            while (current) {
                nodePointer temp = current;
                current = current->next;
                free(temp);
            }
        }
        free(hashTable);
    }
}