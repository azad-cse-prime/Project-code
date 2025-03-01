#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_lc 100
#define INF INT_MAX

typedef struct {
    int source;
    int des;
    int weight;
} Edge;

Edge edges[MAX_lc * MAX_lc];
int edge_count = 0;
int num_loc;
int enemy_defense = -1;

void addEdge(int src, int dest, int weight) {
    edges[edge_count].source = src;
    edges[edge_count].des = dest;
    edges[edge_count].weight = weight;
    edge_count++;
}

void shortestPath(int start, int target) {
    int distance[MAX_lc], previous[MAX_lc];
    int visited[MAX_lc] = {0};

    for (int i = 0; i < num_loc; i++) {
        distance[i] = INF;
        previous[i] = -1;
    }

    distance[start] = 0;

    for (int i = 0; i < num_loc - 1; i++) {
        int minDist = INF, minIndex = -1;
        for (int j = 0; j < num_loc; j++) {
            if (!visited[j] && distance[j] < minDist) {
                minDist = distance[j];
                minIndex = j;
            }
        }

        if (minIndex == -1) break;
        visited[minIndex] = 1;

        for (int j = 0; j < edge_count; j++) {
            int u = edges[j].source, v = edges[j].des, w = edges[j].weight;
            if (u == minIndex && !visited[v] && distance[u] != INF && distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
                previous[v] = u;
            }
        }
    }

    printf("\n=== Mission Status ===\n");
    if (distance[target] == INF) {
        printf("No possible path found! Mission failed!\n");
    } else if (distance[target] > 100) {
        printf("Path found but too costly (%d). Mission failed!\n", distance[target]);
    } else {
        int path[MAX_lc], path_length = 0, intercepted = 0;
        for (int at = target; at != -1; at = previous[at]) {
            if (at == enemy_defense) {
                intercepted = 1;
            }
            path[path_length++] = at;
        }

        if (intercepted) {
            printf("Missile intercepted at node %d! Mission failed!\n", enemy_defense);
        } else {
            printf("Shortest path to destroy enemy missile: ");
            for (int i = path_length - 1; i >= 0; i--) {
                printf("%d%s", path[i], (i > 0 ? " -> " : "\n"));
            }
            printf("Enemy missile destroyed!\n");
        }
    }
}

int main() {
    int num_edges, start, target;
    printf("Enter number of locations (nodes): ");
    scanf("%d", &num_loc);

    printf("Enter number of paths (edges): ");
    scanf("%d", &num_edges);

    printf("Enter paths (source destination weight):\n");
    for (int i = 0; i < num_edges; i++) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(src, dest, weight);
        addEdge(dest, src, weight);
    }

    printf("Enter missile launch base: ");
    scanf("%d", &start);

    printf("Enter enemy missile base: ");
    scanf("%d", &target);

    printf("Enter enemy defense system location (-1 if none): ");
    scanf("%d", &enemy_defense);

    shortestPath(start, target);
}