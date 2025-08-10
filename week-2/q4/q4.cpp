#include <iostream>

using namespace std;

int main(){

    int n;
    cin >> n;

    int a[n];
    for (int i=0;i<n;i++){
        cin >> a[i];
    }

    int revled[n];
    int j = 0;
    int mx = -1e7;
    for (int i=n-1;i>=0;i--){
        if (a[i] >= mx){
            revled[j++] = a[i];
        }
        mx = max(mx, a[i]);
    }

    for (int i=j-1;i>=0;i--){
        cout << revled[i] << " ";
    }cout << endl;
    


    return 0;
}