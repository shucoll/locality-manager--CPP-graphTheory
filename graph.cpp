#include <iostream>
#include <vector>

using namespace std;

void display(vector< vector<int> >&vec,int n) {
    int i=0,j=0;
    cout<<"Display"<<endl;

    for(i = 1 ;i<n;i++) {
        for(j = 1 ;j<n;j++) {
            cout<< vec[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main() {
    int n,x;
    int i,j;
    cout<<"Enter the number"<<endl;
    cin>>n;
    vector<vector<int> > vec( n+1 , vector<int> (n+1));

    for(i=1;i<n+1;i++) {
        for(j=i;j<n+1;j++) {
            if(i==j) {
                vec[i][j]=0;
                continue;
            }
            cout<<"Enter for  "<<i<<"  "<<j<<endl;
            cin>>x;
            vec[i][j]=x;
            vec[j][i]=x;
        }
    }

    display(vec,n+1);
}