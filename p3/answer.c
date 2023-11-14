#include<stdio.h>
#include<stdlib.h>

struct Edge{
    int start;
    int end;
    int weight;
};

int find(int x, int *p){
	if(p[x] < 0){
        return x;
    }
    return p[x] = find(p[x], p);
}

void merge(int x, int y, int *p){        //x root 去跟 y 合併
    int rootX, rootY;
    rootX = find(x, p);
    rootY = find(y, p);
    if(rootX == rootY)
        return;
    if(p[rootX] > p[rootY]){
        p[rootX] = rootY;
    }
    else if(p[rootX] < p[rootY]){
        p[rootY] = rootX;
    }
    else{
        p[rootY] = rootX;
        p[rootX] --;
    }
}

/*void bubbleSort(struct Edge arr[], int n)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j].weight > arr[j + 1].weight) {
                struct Edge temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        // If no two elements were swapped by inner loop,
        // then break
        if (swapped == false)
            break;
    }
}*/
int compare(const void *a,const void *b){
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

int main(){
    int V,E, n1, n2, c, num = 1;
    long long cost = 0;
    scanf("%d%d", &V,&E);
    struct Edge *e = (struct Edge*)malloc(E * sizeof(struct Edge));
    int *p = (int *)malloc(V * sizeof(int));
    for(int i = 0; i < V; i++){
        p[i] = -1;
    }
    //int p[V] = {0};
    for(int i = 0; i < E; i++){
        scanf("%d%d%d", &n1, &n2, &c);
        e[i].start = n1;
        e[i].end = n2;
        e[i].weight = c;
    }
    qsort(e, E, sizeof(struct Edge), compare);
    for(int i = 0; i < E && num <= V -1; i++){
        if(find(e[i].start, p) == find(e[i].end, p)){
            continue;
        }
        else{
            merge(e[i].start, e[i].end, p);
            cost += e[i].weight;
            num++;
        }
    }
    printf("%lld", cost);
    return 0;
}