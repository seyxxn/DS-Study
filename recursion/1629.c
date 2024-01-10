#include <stdio.h>
#include <stdlib.h>
long long a, b, c;
long long solve(long long b);

int main()
{
    scanf("%llu %llu %llu", &a, &b, &c);

    printf("%llu\n", solve(b));

    return 0 ;
}

// 분할 정복 알고리즘 사용 (n:곱하는 횟수)
long long solve(long long n)
{
    if (n == 1) // 1번 곱하는 경우, a를 c로 나눈 나머지를 반환하고 끝남
    {
        return a % c;
    }

    // n을 2로 나누어, 재귀적으로 해결함.
    // 여기서 m은 a^(n/2)를 c로 나눈 나머지
    // 이렇게 하면 문제의 크기를 절반으로 줄일 수 있게 됨
    long long m = solve(n / 2) % c;

    if (n % 2 == 0) // n이 짝수인 경우
    {
        return m * m % c; // a^n = a^(a^(n/2))2 과 같음
    }else { // n이 홀수인 경우
        return m * m % c * a % c; // a^n = a^(a^(n/2))2 * a 와 같음
    }
}

// 큰 수의 거듭제곱을 더 작은 부분으로 나누어 계산하는 방법
// 큰 수를 다룰 때 발생할 수 있는 오버플로우 문제를 방지하고, 계산 효율성을 높임