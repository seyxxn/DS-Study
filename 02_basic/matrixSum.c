// 행렬의 덧셈
#include <stdio.h>
#define MAX_SIZE 2 
int a[2][2] = {{1,1}, {2,2}};
int b[2][2] = {{3,3}, {4,4}};
int c[2][2] = {0};

void add(int a[][MAX_SIZE], int b[][MAX_SIZE], int c[][MAX_SIZE], int rows, int cols){
    int i,j;
    for(i=0; i<rows; i++){
        for(j=0; j<cols; j++){
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

int main(){
    add(a,b,c,2,2);
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            fprintf(stdout, "%d", c[i][j]);
        }
        fprintf(stdout, "\n");
    } 
}