#include <iostream>

using namespace std;

struct intpair{
    int f;
    int s;
};

typedef struct intpair pi;

void swap(int * a, int * b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(){
    int n;
    cin >> n;

    int grid[n][n];
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            cin >> grid[i][j];
        }
    }

    
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            cout << grid[i][j] << " ";
        }cout << endl;
    }

    return 0;
}