#include <bits/stdc++.h>

using namespace std;

template <class T>
class heapSort
{
    int n;
    int par(int curr)
    {
        return curr / 2;
    }

    int lch(int curr)
    {
        return 2 * curr;
    }
    int rch(int curr)
    {
        return 2 * curr + 1;
    }

    bool (*comp)(T &a, T &b);

public:
    T * heap;
    heapSort(int n, T * a, bool (*comp)(T & a, T & b))
    {
        this->comp = comp;
        this->n = n;
        heap = a;
        for (int i = 1; i <= n; i++)
        {
            T s = a[i-1];
            heap[i-1] = s;
            int curr = i;
            while (par(curr) >= 1 && comp(heap[par(curr)-1], heap[curr-1]))
            {
                swap(heap[par(curr)-1], heap[curr-1]);
                curr = par(curr);
            }
        }
    }

    void sort()
    {
        int e = n;
        while (e > 1)
        {
            swap(heap[0], heap[(e--) - 1]);
            int curr = 1;
            while (1)
            {
                int left = lch(curr);
                int right = rch(curr);
                if (left > e && right > e)
                {
                    break;
                }
                else if (left > e)
                {
                    int c3 = comp(heap[curr-1], heap[right-1]);
                    if (!c3)
                        break;
                    swap(heap[curr-1], heap[right-1]);
                    curr = right;
                }
                else if (right > e)
                {
                    int c2 = comp(heap[curr-1], heap[left-1]);
                    if (!c2)
                        break;
                    swap(heap[curr-1], heap[left-1]);
                    curr = left;
                }
                else
                {
                    int c1 = comp(heap[left-1], heap[right-1]);
                    int c2 = comp(heap[curr-1], heap[left-1]);
                    int c3 = comp(heap[curr-1], heap[right-1]);
                    if (c1)
                    {
                        if (!c3)
                            break;
                        swap(heap[curr-1], heap[right-1]);
                        curr = right;
                    }
                    else
                    {
                        if (!c2)
                            break;
                        swap(heap[curr-1], heap[left-1]);
                        curr = left;
                    }
                }
            }
        }
    }
};


template<class T>
class mergeSort{
    int n;
    bool (*comp)(T & a, T & b);
    T * a;
    void merge(int l1, int r1, int l2, int r2){
        int s1 = r1-l1+1;
        int s2 = r2-l2+1;
        T left[s1];
        T right[s2];
        for (int i=0;i<s1;i++){
            left[i] = a[l1+i];
        }
        for (int i=0;i<s2;i++){
            right[i] = a[l2+i];
        }
        int i = 0;
        int j = 0;
        for (int ind=l1;ind<=r2;ind++){
            if (i < s1 && (j >= s2 || comp(left[i], right[j]))){
                a[ind] = left[i++];
            }else{
                a[ind] = right[j++];
            }
        }
    }
    public:

        void sort(int l, int r){
            if (l >= r){
                return;
            }
            int mid = (l+r)/2;
            sort(l, mid);
            sort(mid + 1, r);
            this->merge(l, mid, mid+1, r);
        }
        mergeSort(int n, T * a, bool (* comp)(T & a, T & b)){
            this->a = a;
            this->n = n;
            this->comp = comp;
        }
};


template<class T>
class quickSort{
    int n;
    bool (*comp)(T & a, T & b);
    T * a;
    
    public:
        int partition(int l, int h){
            int p = h;

            int i=l-1;
            for (int j=l;j<h;j++){
                if (comp(a[j], a[p])){
                    swap(a[++i], a[j]);
                }
            }
            swap(a[++i], a[p]);
            return i;
        }

        void sort(int l, int r){
            if (l >= r){
                return;
            }
            int i = partition(l, r);
            sort(l, i-1);
            sort(i+1, r);
        }
        quickSort(int n, T * a, bool (* comp)(T & a, T & b)){
            this->a = a;
            this->n = n;
            this->comp = comp;
        }
};

template<class T>
class Sort{
    public:
        int l;
        int r;
        T * a;
        bool (*comp)(T & a, T & b);
        Sort(int l, int r, T * a, bool (*comp)(T & a, T & b)){
            this->l = l;
            this->r = r;
            this->a = a;
            this->comp = comp;
        }
        int bubbleSort(){
            int swapcnt = 0;
            int n = r-l+1;
            // taking the smallest element as bubble and putting it in front.
            for (int j=0;j<n-1;j++){
                bool changed = 0;
                for (int i=r;i>0;i--){
                    if (comp(a[i], a[i-1])){
                        swap(a[i], a[i-1]);
                        swapcnt += 1;
                        changed = 1;
                    }
                }
                if (!changed){
                    break;
                }
            }
            return swapcnt;
        }

        int insertionSort(){
            int inv = 0;
            for (int i=l+1;i<=r;i++){
                int tmp = a[i];
                bool flag = 0;
                int j;
                for (j=i-1;j>=0;j--){
                    if (comp(tmp, a[j])){
                        a[j+1] = a[j];
                        inv += 1;
                    }else{
                        a[j+1] = tmp;
                        flag = 1;
                        break;
                    }
                }
                if (!flag && j < 0){
                    a[j+1] = tmp;
                }
            }
            return inv;
        }
};

class NCSort{
    int n;
    short ** digitarr;
    int * a;
    int dig;
    public:
        NCSort(int n, int * a, int dig=10){
            this->n = n;
            this->a = a;
            this->dig = dig;
        }
        void radixSort(){
            this->digitarr = (short **) malloc(sizeof(short *) * n);
            for (int i=0;i<n;i++){
                digitarr[i] = (short *) malloc(sizeof(short) * dig);
            }

            int vals[dig];
            for (int i=0;i<n;i++){
                int val = 1;
                for (int j=0;j<dig;j++){
                    digitarr[i][j] = (short)((a[i]/val)%10);
                    vals[j] = val;
                    val *= 10;
                }
            }

            for (int i=0;i<dig;i++){
                short ** tmp = (short **) malloc(sizeof(short *) * n);
                for (int j=0;j<n;j++){
                    tmp[j] = (short *) malloc(sizeof(short) * dig);
                }
                int cnt[10];
                for (int j=0;j<10;j++) cnt[j]=0;
                for (int j=0;j<n;j++){
                    cnt[digitarr[j][i]] += 1;
                }
                int sm = 0;
                for (int j=0;j<10;j++){
                    sm += cnt[j];
                    cnt[j] = sm;
                }
                for (int j=n-1;j>=0;j--){
                    int pos = (cnt[digitarr[j][i]]--) - 1;
                    for (int k=0;k<dig;k++){
                        tmp[pos][k] = digitarr[j][k];
                    }
                }
                for (int j=0;j<n;j++){
                    free(digitarr[j]);
                }
                free(digitarr);
                digitarr = tmp;
            }
            for (int i=0;i<n;i++){
                a[i] = 0;
                for (int j=0;j<dig;j++){
                    a[i] += digitarr[i][j] * vals[j];
                }
            }
        }
};





