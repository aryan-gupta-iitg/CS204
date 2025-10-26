#include <iostream>

using namespace std;
int adj[21][21];

void dfs(int v, int * vis, int n){
    vis[v] = 1;
    cout << v << " ";
    for (int i=0;i<n;i++){
        if (adj[v][i] && !vis[i]){
            dfs(i, vis, n);
        }
    }
}

int main(){

    int n;
    cin >> n;
    int vis[n];
    for (int i=0;i<n;i++){
        vis[i] = 0;
    }
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            cin >> adj[i][j];
        }
    }
    
    for (int i=0;i<n;i++){
        if (!vis[i]) dfs(i, vis, n);
    }
    cout << endl;


    return 0;
}