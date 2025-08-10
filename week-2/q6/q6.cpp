#include <iostream>

using namespace std;

struct pairint{
    int first;
    int second;
};

typedef struct pairint pi;

int main(){

    int n;
    cin >> n;

    int a[n];
    for (int i=0;i<n;i++) cin >> a[i];
    
    pi p = {n, 0};
    pi cum[n];
    for (int i=n-1;i>=0;i--){
        if (p.second < a[i]){
            p = {i, a[i]};
        }
        cum[i] = p;
    }

    int h = a[0];
    pi curr = {0, a[0]};
    int ans = 0;
    while (curr.first < n-1){
        pi rmax = cum[curr.first + 1];
        int i = curr.first + 1;
        int ext = 0;
        if (rmax.second >= curr.first){
            while (i < n && a[i] < curr.second){
                ext += a[i++];
            }
            ans += min(curr.second, a[i]) * (i - curr.first - 1) - ext;
            curr = {i, a[i]};
        }else{
            while (i < rmax.first){
                ext += a[i++];
            }
            ans += min(curr.second, a[i])*(i-curr.first-1) - ext;
            curr = rmax;
        }
        // cout << curr.first << " " << ans << endl;
    }

    cout << ans << endl;

    return 0;
}