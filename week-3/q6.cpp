#include <iostream>
// median of a two sorted arrays in O(n+m)

using namespace std;

int check(int n, int a[], int m, int b[], int mid){
    int val = a[mid];

    int m1 = (n+m+1)/2 - mid - 1;
    if (m1 < 0) m1 = -1;
    int v1;
    if (m1 >= 0 && m1 < m){
        v1 = b[m1];
    }else{
        v1 = -1000000007;
    }
    int p1 = max(v1, a[mid]);
    int p21 = ((mid+1 < n)?a[mid+1]:1e9+7);
    int p22 = ((m1+1 < m)?b[m1+1]:(int)1e9+7);
    int p2 = min(((mid+1 < n)?a[mid+1]:(int)1e9+7), ((m1+1 < m)?b[m1+1]:(int)1e9+7));
    if (a[mid] <= p22 && v1 <= p21){return 1;}
    else if (a[mid] > p22){
        return 2;
    }else{
        return 3;
    }
}

int med(int n, int a[], int m, int b[]){
    // assuming that first 
    int l = 0;
    int h = n-1;

    while (h - l > 1){
        int mid = (h+l)/2;
        int x = check(n, a, m, b, mid);
        if (x == 1){
            int m1 = (n+m+1)/2 - mid - 1;
            if (m1 < 0) m1 = -1;
            int v1;
            if (m1 >= 0 && m1 < m){
                v1 = b[m1];
            }else{
                v1 = -1000000007;
            }
            return max(a[mid], v1);
        }else if (x == 2){
            h = mid;
        }else{
            l = mid;
        }
    }
    if (check(n, a, m, b, h) == 1){
        int m1 = (n+m+1)/2 - h - 1;
        if (m1 < 0) m1 = -1;
        int v1;
        if (m1 >= 0 && m1 < m){
            v1 = b[m1];
        }else{
            v1 = -1000000007;
        }
        return max(a[h], v1);
    }else{
        int m1 = (n+m+1)/2 - l - 1;
        if (m1 < 0) m1 = -1;
        int v1;
        if (m1 >= 0 && m1 < m){
            v1 = b[m1];
        }else{
            v1 = -1000000007;
        }
        return max(a[l], v1);
    }
}

int main(){

    int n;
    cin >> n;
    int m;
    cin >> m;

    int a[n];
    int b[m];

    for (int i=0;i<n;i++) cin >> a[i];
    for (int i=0;i<m;i++) cin >> b[i];
    int ans = -1;
    if (n > m){
        ans = med(n, a, m, b);
    }else{
        ans = med(m, b, n, a);
    }

    cout << ans << endl;
    return 0;

}