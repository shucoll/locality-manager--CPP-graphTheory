#include <iostream>
#include <vector>

using namespace std;


// ------------------------------------- Kruskal's Algorithm --------------------------------------

//   --- Function to display directly connected landmarks with distance --- 
void displayEdge(float edge[][3],int edges) {
    cout<<endl<<endl<<"Source  "<<"Destination  "<<"Distance"<<endl<<endl;
    for(int i = 0 ; i<edges; i++) {

        for(int j = 0 ; j<3 ; j++) {

            cout<<edge[i][j]<<"\t     ";
        }
        cout<<endl;
    }
}

//      ---- Function to perform union for kruskal's algorithm ---- 
void join(int u,int v,int set[]) {

    if(set[u]<set[v]){
        set[u]+=set[v];
        set[v]=u;
    }
    else{
        set[v]+=set[u];
        set[u]=v;
    }
}

//     ---- Function to find parent for kruskal's algorithm ---- 
int find(int u,int set[]){

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

//     ---- Kruskal's algorithm ---- 
void kruskal(float edge[][3],int size,vector< vector<float> >&vec,int edges) {

    vector< vector<float> > res(2, vector<float> (edges-1));

    int *included = new int[edges];
    int *set = new int[size];

    for(int i = 0;i<edges; i++) 
        included[i] = 0;
    
    for(int i = 1; i<size; i++)
        set[i] = -1;
    
    int u,v,i,j,k,n= edges;
    float min=__FLT_MAX__;
    u=v=i=k=0;

    while(i<size-2) {
        min=__FLT_MAX__;
        for(j=0;j<n;j++) {

            if(included[j]==0 && edge[j][2]<min) {
                u=edge[j][0];
                v=edge[j][1];
                min=edge[j][2];
                k=j;
                
            }
        }

        if(find(u,set)!= find(v,set)) {
            res[0][i]=u;
            res[1][i]=v;
            join(find(u,set),find(v,set),set);
            included[k]=1;
            i++;
        }
        else {
            included[k] = 1;
        }
    }

    float total = 0;
    cout<<"The landmarks to be connected to have all landmarks connected in the min distance possible is"<<endl;
    for(i=0;i<size-2;i++){
        cout<<res[0][i]<<" "<<res[1][i]<<endl;
        total += vec[res[0][i]][res[1][i]];
    }
    cout<<"And the total min distance is "<<total<<endl;

    delete[] included;
    delete[] set;
}

//    ---- Function to get 2D matrix with all the edges ---- 
void graphToEdge(vector< vector<float> >&vec, int size, int edges, int display = 0) {

    float edge[edges][3];
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

    if(display != 1)
    kruskal(edge,size,vec,edges);

    else displayEdge(edge,edges);
}
