#include <iostream>
#include <vector>

using namespace std;

void display(vector< vector<int> >&vec,int n) {
    int i=0,j=0;
    cout<<"Display"<<endl;

    for(i =0;i<n;i++) {
        for(j=0;j<n;j++) {
            cout<< vec[i][j]<<endl;
        }
    }
}

int main() {
    int n,x;
    int i,j;
    cout<<"Enter the number"<<endl;
    cin>>n;
    //vector<vector<int> > vec( n , vector<int> (n));
    vector<vector<int> > vec;
    vec.assign( n , vector<int> (n));

    for(i =0;i<n;i++) {
        for(j=0;j<n;j++) {
            cin>>x;
            vec[i][j]=x;
        }
    }

    display(vec,n);
}