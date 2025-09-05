#include <iostream>
#include "../templates/sorting.cpp"
using namespace std;

int main(){

    int n, k;
    cin >> n >> k;

    int a[n];
    for (int i=0;i<n;i++) cin >> a[i];
    Sort<int> st(0, k-1, a, [](int & a, int & b){return a < b;});
    cout << st.bubbleSort() << endl;
    st.l = k;
    st.r = n-1;
    st.bubbleSort();
    for (int i=0;i<n;i++){
        cout << a[i] << " ";
    }cout << endl;

    return 0;
}