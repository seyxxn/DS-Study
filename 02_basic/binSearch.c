#include <stdio.h>
int compare(int x, int y);
int binsearch(int list[], int searchNum, int left, int right);

int main(){
    int list[10] = {1,2,3,4,5,6,7,8,9,10};
    fprintf(stdout, "%d\n", binsearch(list, 8, 0,9));    
    return 0;
}

int compare(int x, int y){
    if (x < y) return -1;
    else if (x == y) return 0;
    else return 1;
}

int binsearch(int list[], int searchNum, int left, int right){
    int middle;

    while(left <= right){
        middle = (left+right)/2;
        switch (compare(list[middle], searchNum))
        {
        case -1 :
            return binsearch(list, searchNum, middle+1, right);
        case 0 :
            return middle;
        case 1 :
            return binsearch(list, searchNum, left, middle-1);
        }
    }
    return -1;
}