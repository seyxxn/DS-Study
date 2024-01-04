// 동적 배열 생성

#include <stdlib.h>
#include <stdio.h>

// 2차원 배열 동적 생성
int **make2dArray(int rows, int cols)
{
    int **x, i;
    x = (int **)malloc(rows * sizeof(int));
    for (i = 0; i < rows; i++)
    {
        *(x + i) = (int *)malloc(cols * sizeof(int));
    }
    return x;
}

int main()
{

    //  1차원 배열 동적 생성
    int *x, n = 5;
    x = (int *)malloc(n * sizeof(int));

    // 2차원 배열 동적 생성
    int **myArray;
    myArray = make2dArray(5,10);
    myArray[2][4] = 6;
    
    for(int i=0; i<5; i++){
        for(int j=0; j<10; j++){
            printf("%d ", myArray[i][j]);
        }
        printf("\n");
    }

    // 동적 할당된 메모리 해제
    for (int i = 0; i < 5; i++) {
        free(myArray[i]);
    }
    free(myArray);
    free(x);

    return 0;
}