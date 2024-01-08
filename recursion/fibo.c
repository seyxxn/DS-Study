#include <stdio.h>

int fibo(int n);

int main(int argc, char *argv[]){
    int input, i;
    fprintf(stdout, "Input a non-negative integer : ");
    scanf("%d", &input);
    for(i = 0; i <= input; i++){
        fprintf(stdout, "%d ", fibo(i));
    }
    fprintf(stdout, "\n");

    return 0;
}

int fibo(int n){
    if (n == 0) return 0;
    if (n == 1) return 1;
    return (fibo(n-1) + fibo(n-2));
}