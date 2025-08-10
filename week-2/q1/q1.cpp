#include <iostream>

using namespace std;

void swap(int * a, int * b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(){

    int n;
    cin >> n;
    int a[n];
    for (int i=0;i<n;i++){
        cin >> a[i];
    }

    int k;
    cin >> k;
    int curr = a[0];
    int pos = 0;
    int st = pos;
    int times = 0;
    while (times <= 1){
        int nxt = (pos-k+n)%n;
        int tmp = a[nxt];
        a[nxt] = curr;
        if (st == pos){
            times += 1;
        }
        curr = tmp;
        pos = nxt;
    }

    for (int i=0;i<n;i++){
        cout << a[i] << " ";
    }cout << endl;

    return 0;
}