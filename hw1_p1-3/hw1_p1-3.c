#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent;
    int rank;
};

// Compare function for qsort
int compare(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

// Function to find the parent of a vertex
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Function to perform union of two subsets
void unionSets(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Function to find the minimum cost spanning tree using Kruskal's algorithm
int kruskal(struct Edge* edges, int V, int E) {
    qsort(edges, E, sizeof(struct Edge), compare);

    struct Subset subsets[V];
    for (int i = 0; i < V; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    int mstWeight = 0;
    for (int i = 0, e = 0; e < V - 1 && i < E; i++) {
        struct Edge nextEdge = edges[i];
        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);
        if (x != y) {
            mstWeight += nextEdge.weight;
            unionSets(subsets, x, y);
            e++;
        }
    }

    return mstWeight;
}

int main() {
    int V, E;
    scanf("%d %d", &V, &E);
    struct Edge edges[E];

    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        edges[i].src = src;
        edges[i].dest = dest;
        edges[i].weight = weight;
    }

    long long minCost = kruskal(edges, V, E);
    printf("%lld\n", minCost);

    return 0;
}
