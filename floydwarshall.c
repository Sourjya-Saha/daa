#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define INF INT_MAX
#define V 3

void printMatrix(int cost[V][V]);

void initialize(int adj[V][V], int cost[V][V], int path[V][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cost[i][j] = adj[i][j];
            if (i == j || adj[i][j] == INF)
                path[i][j] = -1;
            else
                path[i][j] = i;
        }
    }
}

void floydWarshall(int cost[V][V], int path[V][V]) {
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (cost[i][k] != INF && cost[k][j] != INF &&
                    cost[i][j] > cost[i][k] + cost[k][j]) {
                    cost[i][j] = cost[i][k] + cost[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }

        printf("Via %d:\n", k + 1);
        printMatrix(cost);
        printf("\n");
    }
}

void printMatrix(int cost[V][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (cost[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", cost[i][j]);
        }
        printf("\n");
    }
}

void printPath(int path[V][V], int i, int j) {
    if (i == j) {
        printf("%d", i + 1);
        return;
    }
    if (path[i][j] == -1) {
        printf("No path");
        return;
    }
    printPath(path, i, path[i][j]);
    printf(" -> %d", j + 1);
}

void printAllPaths(int cost[V][V], int path[V][V]) {
    printf("Full paths:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i != j) {
                printf("Path from %d to %d: ", i + 1, j + 1);
                if (cost[i][j] == INF) {
                    printf("No path\n");
                } else {
                    printPath(path, i, j);
                    printf(" (Cost: %d)\n", cost[i][j]);
                }
            }
        }
    }
}

int main() {
    int adj[V][V];
    int cost[V][V], path[V][V];
    char input[10];

    printf("Enter adjacency matrix (use INF for no edge):\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%s", input);
            if (strcmp(input, "INF") == 0)
                adj[i][j] = INF;
            else
                adj[i][j] = atoi(input);
        }
    }

    initialize(adj, cost, path);
    floydWarshall(cost, path);
    printAllPaths(cost, path);

    return 0;
}
