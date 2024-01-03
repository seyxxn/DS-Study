#include <stdio.h>
#define SWAP(x,y,t) ((t)=(x), (x)= (y), (y) = (t))

void perm(char *list, int i, int n);

int main(int argc, char *argv[]){
    char txt[4] = {'a', 'b', 'c'};
    perm(txt, 0, 2);

    return 0;
}

void perm(char *list, int i, int n){
    int j, temp;
    if (i == n){
        for (j = 0; j <= n; j++)
            fprintf(stdout, "%c", list[j]);
        fprintf(stdout, "  ");
    }
    else {
        for (j = i; j <= n; j++){
            SWAP(list[i], list[j], temp);
            perm(list, i + 1, n);
            SWAP(list[i], list[j], temp);
        }
    }
}