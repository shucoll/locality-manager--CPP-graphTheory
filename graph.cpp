#include <iostream>
#include <vector>
//#include<limits>

using namespace std;

void display(vector< vector<float> >&vec,int size) {
    int i=0,j=0;
    cout<<"Display"<<endl;

    for(i = 1 ;i<size;i++) {
        for(j = 1 ;j<size;j++) {
            cout<< vec[i][j]<<" ";
        }
        cout<<endl;
    }
}

int leastDistance(float dist[], bool selVer[],int size) {
    float min = __FLT_MAX__ ;
    int minIndex;

    for(int v = 0; v < size; v++) {
        if(selVer[v] == false && 
        dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void printPath(int par[],int i) {

    if(par[i] == - 1)
    return;

    printPath(par,par[i]);
    cout<<" "<<i;

}

void printSolution(float dist[], int par[],int src, int size) {
    cout<<"Vertex "<<"Distance "<<"Path"<<endl;
    for(int i = 1; i<size; i++) {
        cout<<endl<<src<<"->"<<i<<"\t"<<dist[i]<<"\t"<<src;
        printPath(par,i);
    }
}

void dijkstra(vector< vector<float> >&vec,int src,int size) {

    float dist[size];
    bool selVer[size];
    int par[size];

    for(int i = 0; i<size;i++) {
        par[i] = -1;
        dist[i] = __FLT_MAX__;
        selVer[i] = false;
    }

    dist[src] = 0;

    for( int ver = 1; ver < size ; ver++) {

        int u = leastDistance(dist,selVer,size);

        selVer[u] = true;

        for(int v = 1; v<size; v++) {
            if (!selVer[v] && 
                vec[u][v] && 
                dist[u] != __FLT_MAX__ && 
				dist[u] + vec[u][v] < dist[v]) {

                dist[v] = dist[u] + vec[u][v]; 
                par[v] = u;
            }
	
        }   
    }

    
    for(int i=1; i<size;i++) {
        cout<<dist[i]<<" ";
    }
    cout<<endl;
    for(int i=1; i<size;i++) {
        cout<<selVer[i]<<" ";
    }
    cout<<endl;
    for(int i=1; i<size;i++) {
        cout<<par[i]<<" ";
    }
    cout<<endl;

    printSolution(dist,par,src,size);
}

int main() {
    int n;
    float x;
    int i,j;
    int src;
    cout<<"Enter the number of landmarks"<<endl;
    cin>>n;
    vector< vector<float> > vec( n+1 , vector<float> (n+1));

    cout<<"Enter the distances between mentioned lankmark number. If any two landmarks are not connected directly, enter the distance value as 0"<<endl;
    for(i=1;i<n+1;i++) {
        for(j=i;j<n+1;j++) {
            if(i==j) {
                vec[i][j]=0;
                continue;
            }
            cout<<"Enter distance for  "<<i<<"  "<<j<<endl;
            cin>>x;
            vec[i][j]=x;
            vec[j][i]=x;
        }
    }

    display(vec,n+1);

    cout<<"Enter source node "<<endl;
    cin>>src;
    dijkstra(vec,src,n+1);
    
    return 0;
}