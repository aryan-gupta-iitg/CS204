#include <bits/stdc++.h>
#define int long long
using namespace std;
const int INF = 1e15;

template <class T>
class MergeSort{
    bool (*comp)(T &a, T&b);
    void merge(T * a, int l, int mid, int h){
        int n1 = mid-l+1;
        int n2 = h-mid;
        T left[n1];
        T right[n2];
        for (int i=0;i<n1;i++){
            left[i] = a[l+i];
        }
        for (int i=0;i<n2;i++){
            right[i] = a[mid+i+1];
        }
        int i = 0;
        int j = 0;
        for (int p=l;p<=h;p++){
            if (i < n1 && j < n2){
                if (comp(left[i], right[j])){
                    a[p] = left[i++];
                }else{
                    a[p] = right[j++];
                }
            }else if (i < n1){
                a[p] = left[i++];
            }else{
                a[p] = right[j++];
            }
        }
    }
    public:
        MergeSort(bool (*comp)(T & a, T & b)){
            this->comp = comp;
        }
        void mergesort(T * a, int l, int h){
            if (l >= h){
                return;
            }
            int mid = (l+h)/2;
            mergesort(a, l, mid);
            mergesort(a, mid+1, h);
            merge(a, l, mid, h);
        }
};



bool comp(string & a, string & b){
    if (a.size() == b.size()) return a < b;
    else{
        return a.size() < b.size();
    }
}


signed main()
{

    int n;
    cin >> n;
    
    MergeSort<string> ms(comp);

    string a[n];
    for (int i=0;i<n;i++){
        cin >> a[i];
    }
    ms.mergesort(a, 0, n-1);

    for (int i=0;i<n;i++){
        cout << a[i] << endl;
    }

    return 0;
}