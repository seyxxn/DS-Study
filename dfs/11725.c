#include <stdio.h>
#include <stdlib.h>

int **graph;
int *visited;

void dfs(int v, int n);

int main() {
    int n;
    scanf("%d", &n); 

    graph = (int **)malloc((n + 1) * sizeof(int *));
    visited = (int *)malloc((n + 1) * sizeof(int));

    for (int i = 0; i <= n; i++) {
        graph[i] = (int *)malloc((n + 1) * sizeof(int));
        visited[i] = 0;
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a][b] = 1;
        graph[b][a] = 1;
    }

    for (int i = 0; i <= n; i++) {
        free(graph[i]);
    }
    free(graph);
    free(visited);

    return 0;
}

void dfs(int v, int n) {
    visited[v] = 1;
    printf("%d ", v);

    for (int i = 1; i <= n; i++) {
        if (graph[v][i] == 1 && visited[i] == 0) {
            dfs(i, n);
        }
    }
}
