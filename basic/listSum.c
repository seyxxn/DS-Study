// 리스트의 수를 합산 -> 시간 복잡도 O(N)

#include <stdio.h>
float sum(float list[], int n);

int main(){
    float list[3] = {3.3, 3.4, 4.0};
    fprintf(stdout, "%f\n", sum(list, 3));
}

float sum(float list[], int n){
    float tempSum;
    int i;
    for(i = 0; i <= n; i++) tempSum += list[i];
    return tempSum;
}