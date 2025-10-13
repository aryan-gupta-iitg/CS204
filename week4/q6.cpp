#include <iostream>

using namespace std;

template <class T>
int partition(T * a, int l, int h, bool (*comp)(T & a, T & b)){
    int p = h;
    int i=l-1;
    int j=l;
    while (j<=h){
        if (comp(a[j], a[p])){
            swap(a[j++], a[++i]);
        }else{
            j++;
        }
    }
    swap(a[h], a[++i]);
    return i;
}

template <class T>
void quicksort(T * a, int l, int h, bool (*comp)(T & a, T & b)){
    if (l >= h) return;
    int p = partition<T>(a, l, h, comp);
    quicksort<T>(a, l, p-1, comp);
    quicksort<T>(a, p+1, h, comp);
}

int main(){
    int n;
    cin >> n;
    int a[n];
    for (int i=0;i<n;i++){
        cin >> a[i];
    }

    quicksort<int>(a, 0, n-1, [](int & a, int & b){return a < b;});
    for (int i=0;i<n;i++){
        cout << a[i] << " ";
    }cout << endl;
    
    return 0;
}