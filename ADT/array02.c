// 배별이름은 배열의 시작 주소를 나타낸다.
#include <stdio.h>

int main(void){
    int array[] = {0,1,2,3,4};
    printf("0x%X\n", array); // 배열이름
    printf("0x%X\n", &array[0]); // 0번째 배열의 주소
    // 배열이름은 배열의 시작 주소를 나타내기 때문에 둘의 출력 값은 같음
}