#include <iostream>
#include "../templates/sorting.cpp"
using namespace std;

int main(){

    int n;
    cin >> n;

    int a[n];
    for (int i=0;i<n;i++) cin >> a[i];
    Sort<int> st(0, n-1, a, [](int & a, int & b){return a < b;});
    int cnt = st.insertionSort();
    
    for (int i=0;i<n;i++){
        cout << a[i] << " ";
    }cout << endl;

    cout << cnt << endl;

    return 0;
}