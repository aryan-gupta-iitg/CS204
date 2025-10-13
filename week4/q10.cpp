#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

struct vil{
    string name;
    int x, y, u, w;
};
typedef struct vil vil;

bool comp(vil & a, vil & b){
    if (a.u == b.u){
        if (a.w == b.w){
            return a.name < b.name;
        }else{
            return a.w > b.w;
        }
    }else{
        return a.u < b.u;
    }
}

void merge(vil * a, int l, int mid, int h){
    int n1 = mid - l + 1;
    int n2 = h-mid;
    vil left[n1];
    vil right[n2];
    for (int i=0;i<n1;i++){
        left[i] = a[l+i];
    }
    for (int i=0;i<n2;i++){
        right[i] = a[mid+1+i];
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

void mergesort(vil * a, int l, int h){
    if (l >= h)return;
    int mid = (h+l)/2;
    mergesort(a, l, mid);
    mergesort(a, mid+1, h);
    merge(a, l, mid, h);
}

int main(){

    int n, d;
    cin >> n >> d;

    vil a[n];
    for (int i=0;i<n;i++){
        string name;
        cin >> name;
        int x, y, u, w;
        cin >> x >> y >> u >> w;
        a[i] = {name, x, y, u, w};
    }

    mergesort(a, 0, n-1);

    double curr = 0;
    double mx = d;
    cout << "Village Served: ";
    int xl = 0;
    int yl = 0;
    int lft = n;
    for (int i=0;i<n;i++){
        if (curr + sqrt((a[i].x-xl)*(a[i].x-xl) + (a[i].y-yl)*(a[i].y-yl))+sqrt(a[i].x*a[i].x + a[i].y*a[i].y) > mx){
            break;
        }
        lft -= 1;
        curr += sqrt((a[i].x-xl)*(a[i].x-xl) + (a[i].y-yl)*(a[i].y-yl));
        xl = a[i].x;
        yl = a[i].y;
        cout << a[i].name << " ";
    }
    cout << endl;
    curr += sqrt(xl*xl + yl*yl);
    cout << setprecision(4);
    cout << "Total Distance: " << curr << endl;
    cout << "Villages Not Served: " << lft << endl;
    return 0;
}