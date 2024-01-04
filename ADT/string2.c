#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 25
void strnins(char *s, char *t, int i);

int main(){

    int i = 1;

    char string1[MAX_SIZE] = {"amobile"}, *s = string1;
    char string2[MAX_SIZE] = {"uto"}, *t = string2;

    strnins(s,t,i);

    printf("%s\n", s);
}

void strnins(char *s, char *t, int i){
    char string[MAX_SIZE], *temp = string;
    memset(temp, 0, MAX_SIZE);

    if(i<0 && i>strlen(s)){
        fprintf(stderr, "Position is out of bounds\n");
        exit(1);
    }
    if(!strlen(s)){
        strcpy(s,t);
    }else if (strlen(t)){
        strncpy(temp, s, i);
        strcat(temp, t);
        strcat(temp, (s+i));
        strcpy(s, temp);
    }
}