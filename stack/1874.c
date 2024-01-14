#include <stdio.h>
int n;
int top = -1;
void push(int x);
void pop();
int peek();
int num = 0; // 1부터 n까지의 수를 넣는다.
int stack[100001]; 


int main(){
    scanf("%d", &n);

    // 사용자에게 n번 입력 받음
    for(int i = 0; i < n; i++){
        int enter;
        scanf("%d", &enter);

        while(enter != peek()){
                push(++num);
            }
        if(enter == peek()){
            pop();
        }
    }

    if(top != -1){
        printf("NO\n");
    }

    return 0;
}


void push(int x){
    stack[++top] = x;
    printf("+\n");
}

void pop(){
    stack[top--];
     printf("-\n"); 
}

// 스택의 가장 위에 있는 수를 반환하는 함수
int peek(){
    return stack[top];
}
