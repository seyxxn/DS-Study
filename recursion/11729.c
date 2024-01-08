#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef unsigned long long ull;

ull n;
ull count = 0;

void move(ull n, char start, char to);
void hanoi(ull n, char start, char to, char via);

void hanoi(ull n, char start, char to, char via)
{
    if (n == 1)
    {
        move(1, start, to);
    }
    else
    {
        hanoi(n - 1, start, via, to);
        move(1, start, to);
        hanoi(n - 1, via, to, start);
    }
}

void move(ull n, char start, char to)
{
    printf("%c %c\n", start, to);
}

int main()
{
    scanf("%lld", &n);

    printf("%.0f\n", pow(2, n) - 1);
    hanoi(n, '1', '3', '2');
    return 0;
}

// n개의 원판, 3개의 장대
// A B 출력 -> A판의 가장 위에 있는 원판을 B판으로 옮긴다는 의미