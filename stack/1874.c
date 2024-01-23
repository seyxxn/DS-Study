#include <stdio.h>
int n;
int top = -1;
void push(int x);
void pop();
int peek();
int num = 0; // 1부터 n까지의 수를 넣는다.

int stack[100001]; 

// 정답을 저장할 배열을 선언
int ans[100001*2];
int ansTop = -1;
void pushAns();
void arrayPrint();
int isEndNum = 0; // 마지막 숫자를 입력받았는지 확인하는 변수

int main(){
    scanf("%d", &n);

    // 사용자에게 n번 입력 받음
    for(int i = 0; i < n; i++){
        int enter;
        scanf("%d", &enter);

        // 마지막 숫자를 입력받았다면, isEndNum을 1로 바꿈
        if (enter == n){
            isEndNum = 1;
        }
        // 마지막 숫자를 입력했다면,
        // 그 이후부터는 이제 입력한 순서대로 pop만 되어야하기 때문에 
        // 입력한 숫자와 가장 위에 있는 숫자가 다르면 순열을 만들 수 없음
        if(isEndNum && (enter != peek())){
            printf("NO\n");
            return 0;
        }

        while(enter != peek()){
                push(++num);
            }
        if(enter == peek()){
            pop();
        }
    }

    arrayPrint();
    return 0;
}

void pushAns(int x){
    ans[++ansTop] = x;
}

void push(int x){
    stack[++top] = x;
    pushAns(1); // printf("+\n");
}

void pop(){
    stack[top--];
    pushAns(0); // printf("-\n"); 
}

// 스택의 가장 위에 있는 수를 반환하는 함수
int peek(){
    return stack[top];
}

void arrayPrint(){
    for(int i = 0; i <= ansTop; i++){
        if(ans[i] == 1) printf("+\n");
        else if (ans[i] == 0) printf("-\n");
    }
    printf("\n");
}