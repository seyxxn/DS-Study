#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int N, r, c;
void solve(int n, int row, int col);
long long ans = 0;

// 간소화 한 코드

int main()
{
    scanf("%d %d %d", &N, &r, &c);
    solve(N, r, c);
    printf("%llu\n", ans);
    return 0;
}

void solve(int n, int row, int col)
{
    if (n == 0)
        return;
    if (row == 0 && col == 0) // r행 c열이면 무조건 0번째로 방문
        return;

    int half = pow(2, n - 1);                    // 중간을 기점으로 4분할
    long long areaSize = (long long)half * half; // 4분할 시에 한 부분의 크기

    if (row < half && col < half) // 첫번째로 방문 (왼쪽 위칸)
    {
        ans += areaSize * 0;
    }
    else if (row < half && col >= half) // 두번째로 방문 (오른쪽 위칸)
    {
        ans += areaSize * 1;
        col -= half; // 좌표 재설정 반드시 **
    }
    else if (row >= half && col < half) // 세번째로 방문 (왼쪽 아래칸)
    {
        ans += areaSize * 2;
        row -= half;
    }
    else if (row >= half && col >= half) // 네번째로 방문 (오른쪽 아래칸)
    {
        ans += areaSize * 3;
        col -= half;
        row -= half;
    }
    // n-1 재귀함수 사용 ()
    solve(n - 1, row, col);
}