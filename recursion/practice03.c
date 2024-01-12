#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 100
char str1[MAX_LENGTH];
char str2[MAX_LENGTH];
char printStr[MAX_LENGTH];

void solve(int index, int size);
void printArray(char *a, int size);

void printArray(char *a, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%c", a[i]);
    }
    printf("\n");
}

void solve(int index, int size)
{
    if (index == size){
        printArray(printStr, size);
        return;
    }

    printStr[index] = str1[index];
    solve(index + 1, size);

    printStr[index] = str2[index];
    solve(index + 1, size);
}

int main()
{
    printf("Input\n");
    printf("str1 : ");
    scanf("%s", str1);
    printf("str2 : ");
    scanf("%s", str2);

    printf("Output\n");
    solve(0, strlen(str1));

    return 0;
}