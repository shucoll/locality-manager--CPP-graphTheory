#include <iostream>
#include <vector>
#include <sstream>

#include "LQueue.h"

using namespace std;


// ------------------------------------- For Kruskal's Algorithm --------------------------------------

void displayEdge(float edge[][3],int edges) {
    for(int i = 0 ; i<edges; i++) {

        for(int j = 0 ; j<3 ; j++) {

            cout<<edge[i][j]<<" ";
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
void graphToEdge(vector< vector<float> >&vec, int size, int edges) {

    //cout<<edges<<endl;
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
    
    //cout<<edges<<endl;
    //displayEdge(edge,edges);

    kruskal(edge,size,vec,edges);
}



// ------------------------------------- For Dijkstra's Algorithm --------------------------------------

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
    cout<<endl<<endl<<"Landmark "<<"Distance "<<"Path"<<endl;
    if(distn==0) {
        for(int i = 1; i<size; i++) {
            cout<<endl
            <<src<<"->"
            <<i<<"\t"
            <<(dist[i] == __FLT_MAX__ ? 0 : dist[i])<<"\t"
            <<src;
            printPath(par,i);
        }
    }
    else{
        cout<<endl<<src<<"->"<<distn<<"\t"<<dist[distn]<<"\t"<<src;
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


// ------------------------------------- Other Functions --------------------------------------

//       ---- BFS to know if path exixts between two landmarks ---- 
bool isConnected(vector< vector<float> >&vec, int src,int distn, int size) {

    if(src == distn) return true;

    int i = src,j;
    int visited[size];
    for(int k = 0; k<size;k++) {
        visited[k] = 0;
    }

    
    visited[i] = 1;
    qe.enqueue(i);

    while(!qe.isEmpty()) {

        i=qe.dequeue();
        for(j=1;j<size;j++) {

            if(vec[i][j]!=0 && visited[j]==0){
                
                if( j == distn ) return true;
                visited[j] = 1;
                qe.enqueue(j);
            }
        }
    }
    return false;
}

//       ---- DFS to know if the graph is a connected graph ---- 
void DFS(vector< vector<float> >&vec,int start,int size, bool visited[]){
    
    int j;
    if(visited[start]==false){
        //cout<<start;
        visited[start]=true;
        for(j=1;j<size;j++){
            if(vec[start][j]!=0 && visited[j]==0)
            DFS(vec,j,size,visited);
        }
    }
}

//      ---- Function to check the result from DFS and return the connected status ----
bool isConnectedAll(vector< vector<float> >&vec,int size) {

    bool flag = true;
    bool *visited = new bool[size];

    for(int i =1; i<size; i++) {
        visited[i] = false;
    }

    DFS(vec,1,size,visited);

    for(int i =1 ; i<size; i++) {

        if(!visited[i]) flag = false;
    }
    
    delete[] visited;

    return flag;
}



//     ---- Display the Matrix Representation of the graph ---- 
void displayGraph(vector< vector<float> >&vec,int size) {
    int i=0,j=0;
    cout<<endl<<"Matrix representation of the entered values"<<endl;

    for(i = 1 ;i<size;i++) {
        for(j = 1 ;j<size;j++) {
            cout<< vec[i][j]<<" ";
        }
        cout<<endl;
    }
}


//     ---- Function to add new landmarks ---- 
void addLandmark1(int& size, vector< vector<float> >&vec, int& edges) {

    int i,j;
    float val;

    int newLmk; 
    cout<<endl<<"Enter the number of new landmarks: "; cin>>newLmk;

    vector< vector<float> > vec1( newLmk+size , vector<float> (newLmk+size));

    for(i=1; i < newLmk+size ;i++) {

        for(j=i;j < newLmk+size;j++) {
            

            if(i==j) {
                vec1[i][j]=0;
                continue;
            }

            if(i>= size || j>=size) {
                
                cout<<"Enter distance for  "<<i<<" to "<<j<<" :  ";cin>>val;
                vec1[i][j]=val;
                vec1[j][i]=val;
                if(val!= 0)
                    edges++;
            }
            else{
                vec1[i][j] = vec[i][j];
                vec1[j][i] = vec[j][i];
            }
        }

    }

    vec = vec1;
    size += newLmk;
}


//     ---- Function to change distance betwee two landmarks ---- 
void changeDistance(int& size, vector< vector<float> >&vec, int& edges) {
    int newEdg,src=1,distn=1;
    do {
        if (!(src<size && distn<size && src>= 1 && distn>=1)) 
            cout<<"Invalid Input! Enter correct landmark number"<<endl;

        cout<<"Enter source landmark : ";cin>>src;
        cout<<"Enter the destination landmark : ";cin>>distn;
    }while(!(src<size && distn<size && src>= 1 && distn>=1));

    cout<<"Enter the new distance value for "<<src<<" and "<<distn<<" (Enter 0 if you want to remove the connection btween the landmarks)"<<endl;
    cin>>newEdg;

    if(newEdg==0 && vec[src][distn]!=0) edges--;
    else if(newEdg!=0 && vec[src][distn]==0) edges++;
    vec[src][distn] = newEdg;
    vec[distn][src] = newEdg;
}

//     ---- Utility function to check the input from the menus ---- 
int checkInput(string chM) {
    for (int i = 0; i < chM.length(); i++) {
        if (isdigit(chM[i]) == false) 
            return -1;
    }

    int ipM = 0;     
    stringstream ss(chM);
    ss >> ipM;
    return ipM; 
}


//     ---- Main function ---- 
int main() {
    int n;
    float x;
    int i,j;
    int src=1,distn=1,chM,chL;
    int size,edges=0;
    bool check,created=false;
    string choM,choL;

    vector< vector<float> > vec;

    do{
        cout<<endl<<endl<<" -- Main Menu --"<<endl;
        cout<<"  1. Create Locality by adding landmarks"<<endl;
        cout<<"  2. Add more landmarks to the locality"<<endl;
        cout<<"  3. Change distance between two landmarks"<<endl;
        cout<<"  4. Go to locality management Menu to know about your locality"<<endl;
        cout<<"  0. End program"<<endl;

        cout<<" Enter choice  : ";cin>>choM;
        chM = checkInput(choM);

        switch (chM){
            case 1:
                cout<<endl<<"Enter the number of landmarks: "; cin>>n;
                size = n+1;
                vec.assign(size , vector<float> (size));
                
                cout<<endl<<"Enter the distances between mentioned lankmark number. If any two landmarks are not connected directly, enter the distance value as 0"<<endl;

                for(i=1;i<size;i++) {

                    for(j=i;j<size;j++) {

                        if(i==j) {
                            vec[i][j]=0;
                            continue;
                        }
                        cout<<"Enter distance for  "<<i<<" to "<<j<<" :  ";cin>>x;
                        vec[i][j]=x;
                        vec[j][i]=x;
                        if(x!=0)
                            edges++;
                    }
                }
                created = true;

            break;

            case 2:
                if(created)
                    addLandmark1(size,vec,edges);
                else 
                    cout<<"No locality created"<<endl;

            break;

            case 3:
                changeDistance(size,vec,edges);
            break;

            case 4:
                if(!created) {
                    cout<<"No locality created"<<endl;
                    chM = 1;
                }

            break;


            case 0:
            break;
            
            default: cout<<"Invalid Input"<<endl;

        }

    }while(chM!=0 && chM!=4);
    
    if(chM == 0) chL = 0;
    else chL = 1;

    //displayGraph(vec,size);

    while(chL!=0){
        cout<<endl<<endl<<" -- Locality Management Menu --"<<endl;
        cout<<"  1. Get the sortest distance and path from a source landmark to all other landmarks"<<endl;
        cout<<"  2. Get the sortest distance and path from a source landmark to one destination landmarks"<<endl;
        cout<<"  3. Get the sortest path and distance from every landmark to every other landmark"<<endl;
        cout<<"  4. Get the way to connect all landmarks in the min distance possible"<<endl;
        cout<<"  5. Add new landmarks "<<endl;
        cout<<"  6. Change distance between two landmarks"<<endl;
        cout<<"  7. Know if there exists a path between any two landmarks"<<endl;
        cout<<"  8. Know if isolated landmarks exist in the locality"<<endl;
        cout<<"  9. Get the matrix representstaion of the graph"<<endl;
        cout<<"  0. End Program"<<endl;
        cout<<" Enter choice  : ";cin>>choL;

        chL = checkInput(choL);

        switch(chL) {

            case 1:
            do {
                    if (!(src<size && src>=1)) cout<<"Invalid Input! Enter correct landmark number"<<endl;
                    cout<<"Enter source landmark : ";cin>>src;
                }while(!(src<size && src>=1));
                
                Dijkstra(vec,src,size);
            break;

            case 2:
                do {
                    if (!(src<size && distn<size && src>= 1 && distn>=1)) cout<<"Invalid Input! Enter correct landmark number"<<endl;
                    cout<<"Enter source landmark : ";cin>>src;
                    cout<<"Enter the destination landmark : ";cin>>distn;
                }while(!(src<size && distn<size && src>= 1 && distn>=1));
                
                Dijkstra(vec,src,size,distn);
            break;

            case 3:
                for(int i = 1;i<size;i++) {
                    Dijkstra(vec,i,size);
                }
            break;

            case 4:
                check = isConnectedAll(vec,size);
                if(check)
                    graphToEdge(vec,size,edges);
                else cout<<endl<<"Graph not connected"<<endl;
            break;

            case 5:
                addLandmark1(size,vec,edges);
            break;

            case 6:
                changeDistance(size,vec,edges);
            break;

            case 7:
                do {
                    if (!(src<size && distn<size && src>= 1 && distn>=1)) cout<<"Invalid Input! Enter correct landmark number"<<endl;
                    cout<<"Enter source landmark : ";cin>>src;
                    cout<<"Enter the destination landmark : ";cin>>distn;
                }while(!(src<size && distn<size && src>= 1 && distn>=1));

                check = isConnected(vec,src,distn,size);
                if(check) cout<<"Path exists between "<<src<<" and "<<distn<<endl;
                else cout<<"Path doesn't exists between "<<src<<" and "<<distn<<endl;
            break;

            case 8:
                check = isConnectedAll(vec,size);
                if(!check) cout<<"There exist isolated landmarks in the locality "<<endl;
                else cout<<"No isolated landmarks exist ie all landmarks can be reached starting from any one landmark"<<endl;
            break;

            case 9:
                displayGraph(vec,size);
            break;


            case 0:
            break;

            default: cout<<"Invalid input ";
        } 
    }

return 0;
}

