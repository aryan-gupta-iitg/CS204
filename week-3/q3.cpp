#include <iostream>
#include <string>
#include <utility>
using namespace std;

int main(){

    int n;
    cin >> n;

    int a[n];
    for (int i=0;i<n;i++){
        cin >> a[i];
    }
    int i=0; // before i, all are 0s.
    int j=n-1; // after j all are 1s.
    int p = 0; // iterator
    while (p < j){
        if (a[p] == 0){
            swap(a[p], a[i++]);
        }else if (a[p] == 2){
            swap(a[p], a[j--]);
        }else{
            p++;
        }
    }


    for (int i=0;i<n;i++){
        cout << a[i] << " ";
    }cout << endl;
    
    return 0;
}