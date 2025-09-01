#include <iostream>

using namespace std;

int main(){

    int n;
    cin >> n;

    int a[n];
    for (int i=0;i<n;i++){
        cin >> a[i];
    }
    int j = 0;
    int curr = 0;
    for (int i=0;i<n;i++){
        if (a[i]==curr){continue;}
        cout << i << " " << curr << endl;
        while (j < n && a[j] != curr){
            j += 1;
        }
        if (j >= n){j=i+1;curr++;continue;}
        swap(a[j], a[i]);
        j += 1;
    }

    for (int i=0;i<n;i++){
        cout << a[i] << " ";
    }cout << endl;


    return 0;
}