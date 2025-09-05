#include <bits/stdc++.h>

using namespace std;






int main()
{

    int n;
    cin >> n;
    heapSort hs(n);
    hs.sort();

    for (int i=1;i<=n;i++){
        cout << hs.heap[i] << " ";
    }cout << endl;

    return 0;
}