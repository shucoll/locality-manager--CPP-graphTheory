#include<iostream>
using namespace std;
#define I 65535

int edge[7][3];

int set[6]={-1,-1,-1,-1,-1,-1};
int included[7]={0,0,0,0,0,0,0};

void join(int u,int v) {

    if(set[u]<set[v]){
        set[u]+=set[v];
        set[v]=u;
    }
    else{
        set[v]+=set[u];
        set[u]=v;
    }
}

int find(int u){

    int x=u,v=0;
    while(set[x]>0){
        x=set[x];
    }

    while(u!=x){
        v=set[u];
        set[u]=x;
        u=v;
    }
    return x; 
}

int t[2][5];

void krus() {

    int u=0,v=0,i,j,k=0,min=I,n=7;
    i=0;
    while(i<4) {
        min=I;
        for(j=0;j<n;j++){

            if(included[j]==0 && edge[j][2]<min){
                u=edge[j][0];v=edge[j][1];min=edge[j][2];
                k=j;
                
            }
        }
        if(find(u)!= find(v)){
            t[0][i]=u;t[1][i]=v;
            join(find(u),find(v));
            included[k]=1;
            i++;
            // printf("%d  %d %d %d\n",u,v,find(u),find(v));
        }
        else {
            included[k] = 1;
        }
    }

    printf("Spanning Tree\n");
    for(i=0;i<4;i++){
        printf("%d %d\n",t[0][i],t[1][i]);
    }

}



void display(int arr[7][3]) {
    for(int i = 0 ; i<7; i++) {

        for(int j = 0 ; j<3 ; j++) {

            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
}

void graphToEdge(int vec[][6], int size, int edge[7][3]) {
    int i,j;
    int k=0,l=0;
    for(i=1;i<size;i++) {

        for(j=i;j<size;j++) {

            if(vec[i][j]==0) continue;
            edge[l][0] = i;
            edge[l][1] = j;
            edge[l][2] = vec[i][j];

            l++;
        }
        
    }
}

int main() {
    
    int cost[][6] = {{0,0,0,0,0,0},
                     {0,0, 10, 6, 0, 0}, 
                     {0,10, 0, 3, 0, 4}, 
                     {0,6, 3, 0, 5, 0}, 
                     {0,0, 0, 5, 0, 1}, 
                     {0,0, 4, 0, 1, 0 }};

    graphToEdge(cost,6,edge);

    display(edge);

    krus();

    
    
}