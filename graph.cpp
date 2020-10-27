#include <iostream>
#include <vector>
#include <sstream>

#include "LQueue.h"

using namespace std;


// ------------------------------------- For Kruskal's Algorithm --------------------------------------

void displayEdge(float edge[][3],int size) {
    for(int i = 0 ; i<size; i++) {

        for(int j = 0 ; j<3 ; j++) {

            cout<<edge[i][j]<<" ";
        }
        cout<<endl;
    }
}

    //---- Function to perform union for kruskal's algorithm ---- 
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

    //---- Function to find parent for kruskal's algorithm ---- 
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

    //---- Kruskal's algorithm ---- 
void krus(float edge[][3], int size,vector< vector<float> >&vec) {

    vector< vector<float> > res(2, vector<float> (size-1));

    int *included = new int[size+1];
    int *set = new int[size];

    for(int i = 0;i<size+1; i++) 
        included[i] = 0;
    
    for(int i = 0; i<size; i++)
        set[i] = -1;
    
    int u,v,i,j,k,n= size +1;
    float min=__FLT_MAX__;
    u=v=i=k=0;

    while(i<size-2) {
        min=__FLT_MAX__;
        for(j=0;j<n;j++){

            if(included[j]==0 && edge[j][2]<min){
                u=edge[j][0];v=edge[j][1];min=edge[j][2];
                k=j;
                
            }
        }
        if(find(u,set)!= find(v,set)){
            res[0][i]=u;res[1][i]=v;
            join(find(u,set),find(v,set),set);
            included[k]=1;
            i++;
        }
        else {
            included[k] = 1;
        }
    }

    int total = 0;
    cout<<"The landmarks to be connected to have all landmarks connected in the min distance possible is"<<endl;
    for(i=0;i<size-2;i++){
        cout<<res[0][i]<<" "<<res[1][i]<<endl;
        total += vec[res[0][i]][res[1][i]];
    }
    cout<<"And the total min distance is "<<total<<endl;

    delete[] included;
    delete[] set;
}

    //---- Function to get 2D matrix with all the edges ---- 
void graphToEdge(vector< vector<float> >&vec, int size) {

    float edge[size][3];
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
    
    //displayEdge(edge,size);
    krus(edge, size,vec);
}



// ------------------------------------- For Dijkstra's Algorithm --------------------------------------

    //---- Utility function to find the vertex with sortest dist that is not included ---- 
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


    //---- Recursive function to print path ---- 
void printPath(int par[],int i) {

    if(par[i] == - 1)
    return;

    printPath(par,par[i]);
    cout<<" "<<i;

}



    //---- To print entire solution(distance and path) ---- 
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



    //---- Dijkstra's algorithm ---- 
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

   //---- BFS to know if path exixts between two landmarks ---- 
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



   //---- Display the Matrix Representation of the graph ---- 
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


   //---- Function to add new landmarks ---- 
void addLandmark1(int& size, vector< vector<float> >&vec) {

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



   //---- Utility function to check the input from the menus ---- 
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


   //---- Main function ---- 
int main() {
    int n;
    float x;
    int i,j;
    int src=1,distn=1,chM,chL;
    int size;
    bool check;
    string choM,choL;

    vector< vector<float> > vec;

    do{
        cout<<endl<<endl<<"  -- Main Menu --"<<endl;
        cout<<"  1. Create Locality by adding landmarks"<<endl;
        cout<<"  2. Add more landmarks to the locality"<<endl;
        cout<<"  3. Go to locality management Menu to know about your locality"<<endl;
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
                    }
                }

            break;

            case 2:
                addLandmark1(size,vec);

            break;

            case 3:
            break;


            case 0:
            break;
            
            default: cout<<"Invalid Input"<<endl;

        }

    }while(chM!=0 && chM!=3);
    
    if(chM == 0) chL = 0;
    else chL = 1;

    //displayGraph(vec,size);

    while(chL!=0){
        cout<<endl<<endl<<"  --Locality Management Menu --"<<endl;
        cout<<"  1. Get the sortest path and distance from a source landmark to all other"<<endl;
        cout<<"  2. Get the sortest path and distance from a source landmark to one other destination landmarks"<<endl;
        cout<<"  3. Get the sortest path and distance from every landmark to every other landmark"<<endl;
        cout<<"  4. Know if there exists a path between any two landmarks"<<endl;
        cout<<"  5. Get the way to connect all landmarks in the min distance possible"<<endl;
        cout<<"  6. Add new landmarks "<<endl;
        //cout<<"  7. Remove a landmark "<<endl;
        cout<<"  8. Get the matrix representstaion of the graph"<<endl;
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
                do {
                    if (!(src<size && distn<size && src>= 1 && distn>=1)) cout<<"Invalid Input! Enter correct landmark number"<<endl;
                    cout<<"Enter source landmark : ";cin>>src;
                    cout<<"Enter the destination landmark : ";cin>>distn;
                }while(!(src<size && distn<size && src>= 1 && distn>=1));
                check = isConnected(vec,src,distn,size);
                if(check) cout<<"Path exists between "<<src<<" and "<<distn<<endl;
                else cout<<"Path doesn't exists between "<<src<<" and "<<distn<<endl;
            break;

            case 5:
                graphToEdge(vec,size);
            break;

            case 6:
                addLandmark1(size,vec);
            break;

            case 8:
                displayGraph(vec,size);
            break;


            case 0:
            break;

            default: cout<<"Invalid input ";
        } 
    }

return 0;
}

