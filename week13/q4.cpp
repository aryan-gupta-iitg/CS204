#include <iostream>

using namespace std;
const int INF = 1e9+7;
int main(){

    int n;
    cin >> n;

    int adj[n][n];
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            int x;
            cin >> x;
            if (x == 99999){
                adj[i][j] = INF;
            }else{
                adj[i][j] = x;
            }
        }
    }

    // floyd-warshall algo.
    int d[n][n];
    int opt[n][n];
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            d[i][j] = adj[i][j];
            opt[i][j] = n;
        }
    }
    
    for (int k=0;k<n;k++){
        for (int i=0;i<n;i++){
            for (int j=0;j<n;j++){
                if (d[i][j] > d[i][k]+d[k][j]){
                    opt[i][j] = min(opt[i][j], k);
                    d[i][j] = d[i][k]+d[k][j];
                }
            }
        }
    }

    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            if (opt[i][j] != n) cout << opt[i][j] << " ";
            else cout << "_" << " ";
        }cout << endl;
    }

    return 0;
}