// 배열을 선언하거나 초기화하는 방법
#include <stdlib.h> // malloc 사용을 위해서 필요한 헤더파일
#include <stdio.h>

void arrayPrint(int list[], int n)
{
    for (int i = 0; i < n; i++)
    {
        fprintf(stdout, "%d ", list[i]);
    }
    fprintf(stdout, "\n");
}

int main()
{
    int list1[5];

    int list2[] = {1, 2, 3, 4, 5, 6, 7};

    int list3[5] = {[1] = 10, [3] = 20};

    int *list4;
    int n = 5;
    list4 = (int *)malloc(n * sizeof(int));

    int list5[10] = {0};

    arrayPrint(list4, 5);

    return 0;
}
