#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

int n;
void hanoi(int n, char start, char to, char via);
void move(int n, char start, char to);

void hanoi(int n, char start, char to, char via)
{
    if (n == 1)
    {
        move(n, start, to);
    }
    else
    {
        hanoi(n - 1, start, via, to);
        move(n, start, to);
        hanoi(n - 1, via, to, start);
    }
}

void move(int n, char start, char to)
{
    printf("%c %c\n", start, to);
}

// 하노이 원반을 움직이는 횟수 : 2^n-1번 -> 이 때문에, n이 크면 가장큰 자료형 조차 담지 못하게 됨
// 변수 선언을 통해 해결할 수 없는 정수처리이기에, 이 부분은 biginter 함수를 이용하여 unsigned long long 보다 큰 변수를 다루도록 한다.

// Big integer
// 정수형으로 나타낼 수 있는 최대 크기보다 더 큰 수를 나타내고자 할 때 사용하는 방법. 문자열을 이용해야함
void Power(int x, int n, char arr[])
{ // x의 n승을 arr이라는 문자열 배열에 저장하고자 함.
    int temp = 0, last = 0, cnt = 0;
    // temp : 임시로 계산된 값 , last : 결과를 저장하기 위한 배열 arr의 마지막 인덱스, cnt : 올림 값 저장
    arr[0] = 1;
    //  arr[0]을 1로 초기화. 결과 배열 arr의 첫번째 요소에 1을 저장하여 시작한다는 의미 (일반적으로 x의 0승이 1이기 때문에)

    // for 루프를 사용하여 x를 n번 곱한 값을 계산한다. (x^n 이므로)
    // 외부 루프는 n번 반복, 내부 루프는 배열 arr에 현재 저장된 값들을 곱하고, 필요한 올림을 처리
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= last; j++)
        {
            temp = arr[j] * x;
            // 내부루프에서 temp 변수에 현재 배열 arr의 요소와 x를 곱한 값을 저장
            if (temp >= 10)
            { // temp가 10이상이면 올림 처리
                arr[j] = temp % 10 + cnt;
                cnt = temp / 10;

                if (j == last)
                {
                    arr[++last] = cnt;
                    cnt = 0;
                    break; // 반복문을 빠져나감
                }
            } // temp가 10미만이면 올림을 처리하지 않음
            else
            {
                arr[j] = temp + cnt;
                cnt = 0;
            }
        }
    }
    arr[0] -= 1; // 결과배열 arr의 첫번째 요소에서 1을 빼준다.
    // 하노이탑 이동 횟수 2^n - 1 이기 때문

    // arr을 거꾸로 출력하여 최종 결과 표시
    for (int i = last; i >= 0; i--)
        printf("%d", arr[i]);
    printf("\n");
    // printf("%.0f\n", pow(2, n) - 1);
}

int main()
{
    char number[35];

    scanf("%d", &n);
    Power(2, n, number);

    if (n > 20)
        return 0;

    hanoi(n, '1', '3', '2');

    return 0;
}

// n개의 원판, 3개의 장대
// A B 출력 -> A판의 가장 위에 있는 원판을 B판으로 옮긴다는 의미