#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 100
char str1[MAX_LENGTH];
char str2[MAX_LENGTH];

void solve(char *a, char *b, int index)
{
    // 문자열 a의 문자들을 b로 하나씩 복사하는 과정을 재귀함수로 구현할 수 있음

    // 만약 a의 마지막에 도달하면
    if (a[index]== '\0')
    {
        b[index] = '\0'; // 문자열의 끝을 표시
        return;
    }

    b[index] = a[index];    // 문자복사
    solve(a, b, index + 1); // 다음 문자로 복사
}

int main()
{
    printf("Input :\n");
    printf("s1 = ");
    scanf("%s", str1);

    printf("s2 = ");
    scanf("%s", str2);

    printf("Output :\n");
    printf("s2 = ");

    solve(str1, str2, 0);

    printf("%s\n", str2);
    return 0;
}