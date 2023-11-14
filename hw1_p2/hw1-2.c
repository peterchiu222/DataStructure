#include<stdio.h>
#include<string.h>
#include<stdlib.h>
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
void same(int x,int y, int *p){
    if(find(x,p) == find(y,p)){
        printf("true\n");
    }
    else {
        printf("false\n");
    }
}
int main(){
    int x;
    scanf("%d", &x);
    while(x--){
        int n, ops = 0;
        scanf("%d %d", &n, &ops);
        int *p = (int*)malloc(n*sizeof(int));
        for(int i = 0; i < n; i++){
            p[i] = -1;
        }
        while(ops--){
            char buffer[10];
            scanf("%s", buffer);
            if(!strcmp(buffer,"find")){
                int y;
                scanf("%d", &y);
                printf("%d\n", find(y, p));
            }
            else if(!strcmp(buffer, "same")){
                int a, b;
                scanf("%d%d",&a,&b);
                same(a, b, p);
            }
            else if(!strcmp(buffer,"union")){
                int a, b;
                scanf("%d%d", &a, &b);
                merge(a, b, p);
            }
        }
        free(p);
    }
    return 0;
}