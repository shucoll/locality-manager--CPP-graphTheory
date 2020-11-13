#include <iostream>
#include <vector>

using namespace std;

// ------------------------------------- Dijkstra's Algorithm --------------------------------------

//      ---- Utility function to find the vertex with sortest dist that is not included in the path ---- 
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


//     ---- Recursive function to print path ---- 
void printPath(int par[],int i) {

    if(par[i] == - 1)
    return;

    printPath(par,par[i]);
    cout<<" "<<i;

}


//    ---- To print entire solution(distance and path) ---- 
void printSolution(float dist[], int par[],int src, int size,int distn) {
    cout<<endl<<endl<<"Landmark  "<<"Distance  "<<"Path"<<endl;
    if(distn==0) {
        for(int i = 1; i<size; i++) {
            cout<<endl
            <<" "<<src<<"->"
            <<i<<"\t "
            <<(dist[i] == __FLT_MAX__ ? 0 : dist[i])<<"\t   "
            <<src;
            printPath(par,i);
        }
    }
    else{
        cout<<endl<<" "<<src<<"->"
        <<distn<<"\t "
        <<(dist[distn] == __FLT_MAX__ ? 0 : dist[distn])<<"\t   "
        <<src;
        printPath(par,distn);
    }
}



//   ---- Dijkstra's algorithm ---- 
void Dijkstra(vector< vector<float> >&vec,int src,int size,int distn = 0) {

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
    
    printSolution(dist,par,src,size,distn);

}
