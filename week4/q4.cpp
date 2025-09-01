#include <iostream>
#include "../templates/sorting.cpp"
using namespace std;

int main(){

    int n;
    cin >> n;
    int a[n];
    for (int i=0;i<n;i++) cin >> a[i];
    if (n == 1){
        cout << 0 << endl;return;
    }
    NCSort ns(n, a, 10);
    ns.radixSort();
    int ans = 0;
    for (int i=0;i<n-1;i++){
        if (ans < a[i+1]-a[i]){
            ans = a[i+1]-a[i];
        }
    }
    cout << ans << endl;
    return 0;
}