#include <iostream>

using namespace std;
const int INF = 1e9+7;

int main(){

    int n;
    cin >> n;
    int m;
    cin >> m;
    int t;
    cin >> t;
    int adj[n][n];
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            if (i != j) adj[i][j] = INF;
            else adj[i][j] = 0;
        }
    }
    for (int i=0;i<m;i++){
        int u, v, w;
        cin >> u >> v >> w;
        adj[u][v] = w;
        adj[v][u] = w;
    }

    // floyd-warshall algo.
    int d[n][n];
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            d[i][j] = adj[i][j];
        }
    }
    
    for (int k=0;k<n;k++){
        for (int i=0;i<n;i++){
            for (int j=0;j<n;j++){
                d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
            }
        }
    }
    int cnt = INF;
    int cty = -1;
    for (int i=0;i<n;i++){
        int tmp = 0;
        for (int j=0;j<n;j++){
            if (adj[i][j] <= t){
                tmp++;
            }
        }
        if (tmp < cnt){
            cnt = tmp;
            cty = i;
        }else if (tmp == cnt){
            cty = max(cty, i);
        }
    }
    cout << cty << endl;
    return 0;
}