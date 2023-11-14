#include<stdio.h>
#include<stdlib.h>
struct Edge{
    int weight;
    int v1;
    int v2;
};
int find(int *parent, int x) {
    if (parent[x] < 0)
        return x;
    return parent[x] = find(parent, parent[x]);
}

void unionByHeight(int *parent, int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);
    if (rootX == rootY)
        return;
    if (parent[rootX] > parent[rootY]) {//樹根數
        parent[rootX] = rootY;
    } else if (parent[rootX] < parent[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;// If two sets with same height perform union, the first set a1 be the parent
        parent[rootX]--;//長高一格
    }
}

/*void bubble_sort(struct Edge arr[], int n) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      if (arr[j].weight > arr[i].weight) {
        struct Edge temp = arr[j];
        arr[j] = arr[i];
        arr[i] = temp;
      }
    }
  }
}*/

int compareEdges(const void *a, const void *b) {
    struct Edge *edgeA = (struct Edge *)a;
    struct Edge *edgeB = (struct Edge *)b;
    return edgeA->weight - edgeB->weight;
}


int main()
{
    long long cost=0;
    //The first line shows V and E. V represents the vertex number while E is the edge number
    int V,E;
    scanf("%d %d",&V,&E);
    /*
     Each line contains s, t and c, which
     means there is an edge between s and v with cost c.  
    */
    struct Edge* edge = (struct Edge *)malloc(E * sizeof(struct Edge));
   for(int i=0;i<E;i++) 
   {
    int s,t,c;
    scanf("%d %d %d",&s,&t,&c);
    {
        edge[i].weight=c;
        edge[i].v1=s;
        edge[i].v2=t;
    }
   }
   //bubble_sort(edge,E);//由小排到大
   qsort(edge, E, sizeof(struct Edge), compareEdges);
   int *parent = (int *)malloc(V * sizeof(int));
   int n=1;
     for (int i = 0; i < V; i++)//初始化
        parent[i] = -1;
    for(int i=0;i<E;i++)
    {
       if(n>V-1)break;
       if(find(parent,edge[i].v1)!=find(parent,edge[i].v2))
       {
        unionByHeight(parent,edge[i].v1,edge[i].v2);
        cost+=edge[i].weight;
        n++;
       }
    }
    printf("%lld",cost);      
return 0;
}