#include <iostream>
#include <vector>
#include <sstream>

#include "LQueue.h"

#define verlim 101

using namespace std;

bool BFS(vector< vector<float> >&vec, int src,int distn, int size) {

    if(src == distn) return true;

    int i = src,j;
    int visited[size];
    for(int k = 0; k<size;k++) {
        visited[k] = 0;
    }

    //cout<<i;
    visited[i] = 1;
    qe.enqueue(i);

    while(!qe.isEmpty()) {

        i=qe.dequeue();
        for(j=1;j<size;j++) {

            if(vec[i][j]!=0 && visited[j]==0){
                //cout<<j;
                if( j == distn ) return true;
                visited[j] = 1;
                qe.enqueue(j);
            }
        }
    }
    return false;
}

/*
    ---- Display the Matrix Representation of the graph ---- 
*/
void display(vector< vector<float> >&vec,int size) {
    int i=0,j=0;
    cout<<endl<<"Matrix representation of the ented values"<<endl;

    for(i = 1 ;i<size;i++) {
        for(j = 1 ;j<size;j++) {
            cout<< vec[i][j]<<" ";
        }
        cout<<endl;
    }
}

/*
    ---- Utility function to find the vertex with sortest dist vertex that is not included ---- 
*/
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

/*
    ---- Recursive function to print path ---- 
*/
void printPath(int par[],int i) {

    if(par[i] == - 1)
    return;

    printPath(par,par[i]);
    cout<<" "<<i;

}

/*
    ---- To print entire solution(distance and path) ---- 
*/
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

/*
    ---- Dijkstra's algorithm ---- 
*/
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

/*
    ---- To add new landmarks to exixting graph ---- 
*/
void addLandmark(int& size, vector< vector<float> >&vec) {

    int i,j;
    float val;

    int newLmk; 
    cout<<endl<<"Enter the number of new landmarks: "; cin>>newLmk;


    while(size+newLmk > 100 || newLmk < 0) {

        if (newLmk < 0) 
            cout<<"Can't add negative landmark numbers"<<endl;

        else 
            cout<<"Can't add landmarks. Size limit exceeded"<<endl;


        cout<<endl<<"Enter the number of new landmarks: "; cin>>newLmk;
    }

    for(i=1; i < newLmk+size ;i++) {

        for(j=i;j < newLmk+size;j++) {

            if(i >= size || j>=size) {
                
                if(i==j) {
                    vec[i][j]=0;
                    continue;
                }
            
                cout<<"Enter distance for  "<<i<<" to "<<j<<" :  ";cin>>val;
                vec[i][j]=val;
                vec[j][i]=val;
            }
        }

    }

    size += newLmk;
} 

/*
    ---- To check the input from the menus ---- 
*/
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



int main() {
    int n;
    float x;
    int i,j;
    int src=1,distn=1,chM,chL;
    int size;
    bool check;

    vector< vector<float> > vec( verlim , vector<float> (verlim));

    do{
        cout<<endl<<endl<<"  -- Main Menu --"<<endl;
        cout<<"  1. Create Locality by adding landmarks"<<endl;
        cout<<"  2. Add more landmarks to the locality"<<endl;
        cout<<"  3. Go to locality management Menu to know about your locality"<<endl;
        cout<<"  0. End program"<<endl;

        cout<<" Enter choice  : ";cin>>chM;

        switch (chM){
            case 1:
                cout<<endl<<"Enter the number of landmarks: "; cin>>n;
                size = n+1;
                
                while(size > 100){
                    cout<<"Can't create graph. Size limit exceeded"<<endl;
                    cout<<endl<<"Enter the number of landmarks: "; cin>>n;
                }

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
                addLandmark(size,vec);

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

    display(vec,size);

    while(chL!=0){
        cout<<endl<<endl<<"  --Locality Management Menu --"<<endl;
        cout<<"  1. Get the sortest path and distance from one source landmark to all other"<<endl;
        cout<<"  2. Get the sortest path and distance from one source landmark to one other destination landmarks"<<endl;
        cout<<"  3. Get the sortest path and distance from every landmark to every other landmark"<<endl;
        cout<<"  4. Know if there exists a path between any two landmarks"<<endl;
        cout<<"  5. Go to all lankmarks starting from one source landmark- path 2"<<endl;
        cout<<"  6. Add more landmarks "<<endl;
        cout<<"  7. Remove a landmark "<<endl;
        cout<<"  0. End Program"<<endl;
        cout<<" Enter choice  : ";cin>>chL;

        switch(chL) {
            case 1:
            do {
                if (!(src<size && src>=1)) cout<<"Invalid Input! Enter correct landmark number"<<endl;
                cout<<"Enter source node : ";cin>>src;
            }while(!(src<size && src>=1));
            Dijkstra(vec,src,size);
            break;

            case 2:
                do {
                    if (!(src<size && distn<size && src>= 1 && distn>=1)) cout<<"Invalid Input! Enter correct landmark number"<<endl;
                    cout<<"Enter source node : ";cin>>src;
                    cout<<"Enter the destination node : ";cin>>distn;
                }while(!(src<size && distn<size && src>= 1 && distn>=1));
                
                Dijkstra(vec,src,size,distn);
            break;

            case 3:
                for(int i = 1;i<size;i++) {
                    Dijkstra(vec,i,size);
                }
            break;

            case 4:
                cout<<"Enter the source landmark: ";cin>>src;
                cout<<"Enter the distination landmark: ";cin>>distn;
                check = BFS(vec,src,distn,size);
                if(check) cout<<"Path exists between "<<src<<" and "<<distn<<endl;
                else cout<<"Path doesn't exists between "<<src<<" and "<<distn<<endl;
            break;

            case 6:
                addLandmark(size,vec);

            break;

            case 0:
            break;

            default: cout<<"Invalid input ";
        } 
    }

return 0;
}

