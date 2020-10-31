#include<iostream>
#include<vector>

using namespace std;

void DFS(int vec[][6],int start,int size, bool visited[])
{
    //static bool visited[6] = {false};
    int j;
    if(visited[start]==false){
        cout<<start;
        visited[start]=true;
        for(j=1;j<size;j++){
            if(vec[start][j]!=0 && visited[j]==0)
            DFS(vec,j,size,visited);
        }
    }
}

bool isConnected1(int vec[][6],int size) {

    bool flag = true;
    
    bool *visited = new bool[size];

    for(int i =1; i<size; i++) {
        visited[i] = false;
    }
    

    DFS(vec,1,size,visited);
    //DFS(vec,1,size);


    
    for(int i =1 ; i<size; i++) {

        if(!visited[i]) flag = false;
    }
    
    delete[] visited;
    

    return flag;
}


int main() {

    int G[][6] =    {{0,0,0,0,0,0},
                    {0,0,10,6,0,0}, 
                    {0,10,0,3,0,4}, 
                    {0,6,3,0,5,0}, 
                    {0,0,0,5,0,1}, 
                    {0,0,4,0,1,0}};

    bool check = isConnected1(G,6);

    cout<<endl<<check<<endl;

}