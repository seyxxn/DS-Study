#include <stdio.h>
void hanoi(int n, char start, char to, char via);
void move(int n, char start, char to);

void hanoi(int n, char start, char to, char via){
    if (n == 1){
        move(1, start, to); 
    }else{
        hanoi(n-1, start, via, to);
        move(n, start, to);
        hanoi(n-1, via, to, start);
    }
}

void move(int n, char start, char to){
    printf("%d번 원판을 %c에서 %c로 옮긴다 \n", n, start, to);
}

int main(void){
    int n = 0;
    printf("원반 개수 입력 : ");
    scanf("%d", &n);

    hanoi(n, 'A', 'C', 'B');

    return 0;
}