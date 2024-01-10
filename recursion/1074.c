#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int N, r, c;
void solve(int n, int row, int col);
long long ans = 0;

int main()
{
    scanf("%d %d %d", &N, &r, &c);
    solve(N, r, c);
    printf("%llu\n", ans);
    return 0;
}

void solve(int n, int row, int col)
{
    if (row == 0 && col == 0) // r행 c열이면 무조건 0번째로 방문
        return;

    int half = pow(2, n - 1); // 중간을 기점으로 4분할
    long long areaSize = (long long)half * half;

    if (n == 1)
    {
        if (row < half && col < half) // 첫번째로 방문 (왼쪽 위칸)
        {
            ans += 0;
        }
        else if (row < half && col >= half) // 두번째로 방문 (오른쪽 위칸)
        {
            ans += 1;
        }
        else if (row >= half && col < half) // 세번째로 방문 (왼쪽 아래칸)
        {
            ans += 2;
        }
        else if (row >= half && col >= half) // 네번째로 방문 (오른쪽 아래칸)
        {
            ans += 3;
        }
        return;
    }
    else
    {
        if (row < half && col < half) // 첫번째로 방문 (왼쪽 위칸)
        {
            ans += areaSize * 0;
            solve(n - 1, row, col);
        }
        else if (row < half && col >= half) // 두번째로 방문 (오른쪽 위칸)
        {
            ans += areaSize * 1;
            solve(n - 1, row, col - half);
        }
        else if (row >= half && col < half) // 세번째로 방문 (왼쪽 아래칸)
        {
            ans += areaSize * 2;
            solve(n - 1, row - half, col);
        }
        else if (row >= half && col >= half) // 네번째로 방문 (오른쪽 아래칸)
        {
            ans += areaSize * 3;
            solve(n - 1, row - half, col - half);
        }
    }
}