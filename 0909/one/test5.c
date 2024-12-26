#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
    char gender[10];
} UserInfo;

void inputUserInfo(UserInfo* user);
void printUserInfo(const UserInfo* user);

int main () {
    UserInfo user;

    inputUserInfo(&user);
    printUserInfo(&user);

    return 0;
}

void inputUserInfo(UserInfo* user) {
    printf("이름을 입력하세요: ");
    scanf("%s", &user[0].name); //user -> name 으로 해도 된다.
    printf("\n나이를 입력하세요: ");
    scanf("%d", &user[0].age);
    printf("\n성별을 입력하세요: ");
    scanf("%s", &user[0].gender); 
}

void printUserInfo(const UserInfo* user) {
    printf("\n\n--- 사용자 정보 ----\n");
    printf("%s\n", user[0].name);
    printf("%d\n", user[0].age);
    printf("%s", user[0].gender);
}