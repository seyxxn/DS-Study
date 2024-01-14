#include <stdio.h>
int k;
int stack[100001];
int top = -1;
int ans  = 0;
void push();
void pop();
void solve();

int main(){
    scanf("%d", &k); 
    for (int i = 0; i < k; i++){
        int enter; 
        scanf("%d", &enter);
        if (enter == 0){
            pop();
        }else{
            push(enter);
        }
    }
    solve();
    return 0;
}

void push(int x){
    stack[++top] = x;
}

void pop(){
    stack[top--];
}

void solve(){
    for(int i = 0; i <= top; i++){
        ans += stack[i];
    }
    printf("%d", ans);
}