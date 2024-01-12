#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 100
char str1[MAX_LENGTH];
char str2[MAX_LENGTH];

void solve(char *a, char *b, int lenA, int lenB)
{
    if (lenA == lenB && lenB <= 0)
    {
        return; // 복사 끝남
    }

    for (int i = 0; i < lenA; i++)
    {
        b[i] = a[i];
    }

    for (int j = lenA; j < lenB; j++)
    {
        b[j] = '\0';
    }
}

int main()
{
    printf("Input :\n");
    printf("s1 = ");
    scanf("%s", str1);
    int length1 = strlen(str1);
    printf("s2 = ");

    scanf("%s", str2);
    int length2 = strlen(str2);

    printf("Output :\n");
    printf("s2 = ");

    solve(str1, str2, length1, length2);
    printf("%s", str2);
    return 0;
}