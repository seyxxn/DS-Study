## N-퀸 문제(N-Queens Problem)

- N X N 크기의 체스판에서 N개의 퀸 기물끼리 서로 공격할 수 없도록 배치하는 경우의 수를 계산하는 문제
- 퀸 기물은 체스에서 가로, 세로, 대각선으로 이동할 수 있는 기물

### 백 트래킹 (BackTracking Algorithms)

- 백 트래킹 알고리즘은 "가능한 모든 방법을 탐색한다"의 아이디어를 가짐.
- 즉, 백 트래킹은 현재 상태에서 가능한 모든 후보군을 따라 들어가며 해결책에 대한 후보를 구축해 나아가다, 가능성이 없다고 판단되면 즉시 후보를 포기하고 부모노드(이전노드)로 돌아가서 다시 탐색하는 범용적인 알고리즘이다.
- 대표적인 완전 탐색 방법으로는 DFS(Depth First Search, 깊이 우선 탐색)이 있다. DFS는 재귀 호출을 통해 특정 노드의 인접 노드가 방문할 장소가 있다면 그쪽으로 이동하여 탐색하는 알고리즘이다.
- 정리 ) DFS를 수행하는 도중 방문한 노드가 가능성이 없는 노드라면 다시 부모 노드로 돌아가서 다른 노드를 탐색하는 방법이 백트래킹 알고리즘이다.

## N-퀸 문제 해결 방법

체스판에 퀸을 새롭게 놓을 때마다 확인해야하는 것은 다음과 같다.

```
1. 상하좌우 같은 줄에 이미 위치한 퀸이 있는가?
2. 대각선의 같은 줄에 이미 위치한 퀸이 있는가?
3. 현재 놓는 퀸이 N번째(마지막) 퀸인가?
```

- 1번과 2번
  - 1번과 2번에 해당하는 경우, 다음 퀸을 놓지 않아도 된다.
  - 이전 상태로 돌아가서 다시 퀸을 놓는다. -> **백트래킹 알고리즘**
  - 1번과 2번에 해당하지 않는 경우에는 다음 퀸을 놓는다.
- 3번
  - 현재 놓는 퀸이 N번째 퀸인 경우는 정답이므로 퀸을 놓는 경우의 수를 1 추가한다.
  - 현재 놓는 퀸이 N번째 퀸이 아닌 경우에는 다음 퀸을 놓는다.

## 핵심 코드

- 체스판을 나타내는 배열을 나타내기 위해 2차원 배열로 구현할 수 있지만, N-퀸 문제 특성상 무조건 한 행에 하나의 퀸을 배치하기 때문에 1차원 배열로도 충분히 구현이 가능하다.

```
temp[1] = 2; // 1행 2열에 퀸이 있다.
temp[2] = 4; // 2행 4열에 퀸이 있다.
temp[3] = 1; // 3행 1열에 퀸이 있다.
temp[4] = 3; // 4행 3열에 퀸이 있다.
```

- main 함수

```
int main(void)
{
    scanf("%d", &n); // 사용자에게 N의 크기를 입력 받음
    temp = (int *)malloc(sizeof(int) * n); // 동적할당

    if (temp == NULL) // 메모리 할당 실패
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        temp[0] = i; // 0행 i열에 퀸을 놓고
        nqueens(1); // 1열부터 배치한다.
    }

    printf("%d\n", cnt);

    free(temp);

    return 0;
}
```

- for문을 통해 각각의 열에 퀸을 하나씩 배치해보는 것은 N-퀸 문제를 해결하는 전형적인 백트래킹 알고리즘의 일부이다.
- 이 반복문은 첫 번째 열에 퀸을 각 행에 놓고, 그 후 nquees 함수를 호출하여 나머지 열에 대한 퀸의 배치를 찾는 과정을 시작한다.
- `temp[0] = i` 는 첫 번째 열에 i번째 행에 퀸을 놓는 시도를 의미한다.
- `nqueens(1)`은 나머지 열에 대한 퀸의 배치를 찾는 재귀적인 과정을 진행한다. 이 함수내에서 현재 열에 퀸을 놓을 수 있는 모든 경우의 수를 확인하고 가능한 경우에는 다음 열로 이동하여 같은 과정을 반복한다.
- 이렇게 모든 열에 대한 퀸의 배치를 찾으면 nqueens 함수내에서 cnt를 증가시킨다.

- nqueens 함수

```
void nqueens(int col)
{
    if (col == n) // 모든 열에 퀸이 배치된 경우, 해를 찾은 경우이므로 cnt 증가
    {
        cnt += 1;
        return ;
    }

    for (int i = 0; i < n; i++) // 반복문을 통해 현재 열에 대해 가능한 퀸의 위치를 시도
    {
        int check = 1; // 퀸을 놓을 수 있는지 여부를 나타내는 변수
        for (int j = 0; j < col; j++) // 현재 열 이전의 열들에 대해 반복
        {
            temp[col] = i; // 현재 열에 퀸을 i번째 행에 놓는 시도
            if (temp[j] == temp[col] || abs(j-col) == abs(temp[j] - temp[col]))
            { // 현재 위치가 이전 열에 배치된 퀸들과 충돌하는지 확인 (같은 행에 퀸이 있는지, 대각선에 있는지)
                check = 0; // 충돌 발생시, check = 0으로 설정하고 반복문 탈출
                break;
            }
        }

        // 퀸을 계속 놓을 수 있다면, 다음 열로 넘어감
        if (check){
            nqueens(col + 1);
        }
    }
}
```
-   nqueens 함수는 주어진 열에서 퀸을 배치하는 함수이다. 현재 열에 대해 가능한 모든 퀸의 위치를 시도하고, 가능한 경우에는 재귀적으로 다음 열로 넘어가며 퀸의 배치를 찾아나간다.
