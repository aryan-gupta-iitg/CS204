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

    pi l = {0, 0};
    pi r = {0, n-1};

    for (int i=0;i<n;i++){
        swap(&grid[l.f][l.s], &grid[r.f][r.s]);
        l.f += 1;
        l.s += 1;
        r.f += 1;
        r.s -= 1;
    }

    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            cout << grid[i][j] << " ";
        }cout << endl;
    }

    return 0;
}