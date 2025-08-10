#include <iostream>

using namespace std;

int main(){

    int n;
    cin >> n;
    int sm = 0;
    for (int i=0;i<(n-1);i++){
        int x;
        cin >> x;
        sm += x;
    }
    
    cout << ((n*(n+1))/2 - sm) << endl;

    return 0;
}