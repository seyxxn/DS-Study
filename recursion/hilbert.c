#include <stdio.h>

void hilbertCurce(int x, int y, int length, int level){
    if (level == 0){
        printf("Draw line from (%d %d) to (%d %d)\n", x , y, x + length, y);
        return;
    }

    int newLength = length / 2;

    hilbertCurce(x, y + newLength, newLength, level - 1);
    hilbertCurce(x + newLength, y, newLength, level-1);
    hilbertCurce(x + newLength, y + newLength, newLength, level -1);
    hilbertCurce(x + 2 * newLength, y + newLength, newLength, level - 1);
    hilbertCurce(x + 2 * newLength, y, newLength, level - 1);
    hilbertCurce(x + 3 * newLength, y, newLength, level - 1);
    hilbertCurce(x + 3 * newLength, y + newLength, newLength, level - 1);
    hilbertCurce(x + 4 * newLength, y + newLength, newLength, level - 1);
}

int main(){
    int canvasSize = 4;
    int initialX = 0;
    int initialY = 0;
    int initialLength = canvasSize;
    int initialLevel = 4;

    hilbertCurce(initialX, initialY, initialLength, initialLevel);

    return 0;
}