#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void findExpressionsRecursive(char* input, char* expr, int pos, int len, int prev, int curr, int target) {
    if (pos == len) {
        if (curr == target) {
            printf("%s\n", expr);
        }
        return;
    }

    for (int i = pos; i < len; i++) {
        char numStr[10];
        strncpy(numStr, &input[pos], i - pos + 1);
        numStr[i - pos + 1] = '\0';
        int num = atoi(numStr);

        if (pos == 0) {
            snprintf(expr + strlen(expr), 100 - strlen(expr), "%d", num);
            findExpressionsRecursive(input, expr, i + 1, len, num, num, target);
            expr[strlen(expr) - strlen(numStr)] = '\0';
        } else {
            // Add
            snprintf(expr + strlen(expr), 100 - strlen(expr), "+%d", num);
            findExpressionsRecursive(input, expr, i + 1, len, num, curr + num, target);
            expr[strlen(expr) - strlen(numStr) - 1] = '\0';

            // Subtract
            snprintf(expr + strlen(expr), 100 - strlen(expr), "-%d", num);
            findExpressionsRecursive(input, expr, i + 1, len, -num, curr - num, target);
            expr[strlen(expr) - strlen(numStr) - 1] = '\0';

            // Multiply
            snprintf(expr + strlen(expr), 100 - strlen(expr), "*%d", num);
            findExpressionsRecursive(input, expr, i + 1, len, prev * num, curr - prev + (prev * num), target);
            expr[strlen(expr) - strlen(numStr) - 1] = '\0';
        }
    }
}

void findExpressions(char* input, int target) {
    char expr[100] = {0};
    findExpressionsRecursive(input, expr, 0, strlen(input), 0, 0, target);
}

int main() {
    char numbers[100];
    int target;

    printf("Input : ");
    scanf("%s", numbers);

    printf("Target : ");
    scanf("%d", &target);

    printf("Output : \n");
    findExpressions(numbers, target);

    return 0;
}
