#include <bits/stdc++.h>

using namespace std;

struct pi{
    int f;
    int s;
};
typedef struct pi pi;

int main(){

    int n;
    cin >> n;

    int a[n];
    for (int i=0;i<n;i++){
        cin >> a[i];
    }

    pi r[n];

    pi tmp = {-1, n};
    for (int i=n-1;i>=0;i--){
        r[i] = tmp;
        if (a[i] > tmp.f){
            tmp = {a[i], i};
        }
    }
    int ans = 0;
    int j = 0;
    while (j < n-1){
        auto rl = r[j];
        if (rl.f <= a[j]){
            int curr = 0;
            int h = min(rl.f, a[j]);
            j++;
            while (j < rl.s){
                curr += max(0, h-a[j]);
                j++; 
            }
            ans += curr;
        }else{
            int curr = 0;
            int ini = j;
            while (a[j] <= a[ini]){
                j++;
            }
            int h = min(a[j], a[ini]);
            for (int l=ini+1;l<j;l++){
                curr += max(0, h-a[l]);
            }
            ans += curr;
        }
    }
    cout << ans << endl;

    return 0;
}