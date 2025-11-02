#include <iostream>

using namespace std;

template <class T>
class MaxHeap{
    T * hp;

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
    int sz;
    int n;
    public:
        MaxHeap(int n, bool (*comp)(T & a, T & b)){
            this->hp = (T *) malloc(sizeof(T) * (n+1));
            this->comp = comp;
            this->sz = 0;
            this->n = n;
        }

        ~MaxHeap(){
            free(this->hp);
            this->hp = nullptr;
        }

        void add(T nw){
            if (this->sz >= this->n){return;}
            hp[++sz] = nw;
            int curr = sz;
            auto & heap = hp;
            while (par(curr) >= 1 && comp(heap[par(curr)], heap[curr]))
            {
                swap(heap[par(curr)], heap[curr]);
                curr = par(curr);
            }
        }

        void pop(){
            if (this->sz <= 0) return;
            int & e = sz;
            auto & heap = hp;
            swap(heap[1], heap[(e--)]);
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
                    int c3 = comp(heap[curr], heap[right]);
                    if (!c3)
                        break;
                    swap(heap[curr], heap[right]);
                    curr = right;
                }
                else if (right > e)
                {
                    int c2 = comp(heap[curr], heap[left]);
                    if (!c2)
                        break;
                    swap(heap[curr], heap[left]);
                    curr = left;
                }
                else
                {
                    int c1 = comp(heap[left], heap[right]);
                    int c2 = comp(heap[curr], heap[left]);
                    int c3 = comp(heap[curr], heap[right]);
                    if (c1)
                    {
                        if (!c3)
                            break;
                        swap(heap[curr], heap[right]);
                        curr = right;
                    }
                    else
                    {
                        if (!c2)
                            break;
                        swap(heap[curr], heap[left]);
                        curr = left;
                    }
                }
            }
        }

        T top(){
            return this->hp[1];
        }

        bool empty(){
            return (sz == 0);
        }

        int size(){
            return sz;
        }

        bool full(){
            return (sz >= n);
        }
    
        void show(){
            int e = this->sz;
            auto & heap = this->hp;
            while (e > 1)
            {
                swap(heap[1], heap[(e--)]);
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
                        int c3 = comp(heap[curr], heap[right]);
                        if (!c3)
                            break;
                        swap(heap[curr], heap[right]);
                        curr = right;
                    }
                    else if (right > e)
                    {
                        int c2 = comp(heap[curr], heap[left]);
                        if (!c2)
                            break;
                        swap(heap[curr], heap[left]);
                        curr = left;
                    }
                    else
                    {
                        int c1 = comp(heap[left], heap[right]);
                        int c2 = comp(heap[curr], heap[left]);
                        int c3 = comp(heap[curr], heap[right]);
                        if (c1)
                        {
                            if (!c3)
                                break;
                            swap(heap[curr], heap[right]);
                            curr = right;
                        }
                        else
                        {
                            if (!c2)
                                break;
                            swap(heap[curr], heap[left]);
                            curr = left;
                        }
                    }
                }
            }
            reverse(this->hp+1, this->hp + sz + 1);
            for (int i=1;i<=sz;i++){
                cout << this->hp[i].first << " " << this->hp[i].second << endl;
            }cout << endl;
        }
};

template <class F, int N>
class Array{
    int ind = 0;
    F arr[N];
    void initializer(){}
    template<typename... Args>
    void initializer(F val, Args...args){
        if (ind >= N){
            return;
        }
        arr[ind++] = val;
        initializer(args...);
    }
    public:
        Array(){
            if (N <= 0){
                throw "Invalid size";
            }
            ind = 0;
        }

        template<typename... Args>
        Array(F val, Args...args){
            if (N <= 0){
                throw "Invalid size";
            }
            ind = 0;
            arr[ind++] = val;
            initializer(args...);
        }

        F& operator[](int i){
            if (i < N){
                return arr[i];
            }
            return arr[0];
        }
        bool operator>(const Array & b) const {
            for (int i=0;i<N;i++){
                if (arr[i] > b.arr[i]){
                    return 1;
                }else if (arr[i] < b.arr[i]){
                    return 0;
                }
            }
            return 0;
        }
        bool operator<(const Array & b) const {
            for (int i=0;i<N;i++){
                if (arr[i] < b.arr[i]){
                    return 1;
                }else if (arr[i] > b.arr[i]){
                    return 0;
                }
            }
            return 0;
        }
        bool operator==(const Array & b) const {
            for (int i=0;i<N;i++){
                if (arr[i] != b.arr[i]){
                    return 0;
                }
            }
            return 1;
        }
};

struct dsu{
    int * parent, * set_size;
    int n;
    dsu(int n){
        parent = new int[n];
        set_size = new int[n];
        for (int i = 0; i < n; i++){
            parent[i] = i;
            set_size[i] = 1;
        }
    }
    int find(int v){
        if(v == parent[v]) return v;
        return parent [v] = find (parent [v]);
    }
    void set_union (int a, int b){
        a = find(a);
        b = find (b);
        if(a != b){
            if(set_size[a] < set_size [b]){
                swap (a, b) ;
            }
            parent[b] = a;
            set_size[a] += set_size[b];
        }   
    }
};

bool comp(Array<int, 3> & a, Array<int, 3> & b){
    int N = 3;
    for (int i=0;i<N;i++){
        if (a[i] > b[i]){
            return 1;
        }else if (a[i] < b[i]){
            return 0;
        }
    }
    return 0;
}

int main(){

    int n, m;
    cin >> n >> m;
    const int N = n;
    MaxHeap<Array<int, 3> > edges(m+1, comp);
    MaxHeap<Array<int, 3> > out(m+1, comp);
    for (int i=0;i<m;i++){
        int u, v, w;
        cin >> u >> v >> w;
        edges.add(Array<int, 3>(w, u, v));
    }
    struct dsu ds(n+1);
    int cost = 0;
    while (edges.size() > 0){
        auto curr = edges.top();
        edges.pop();
        if (ds.parent[curr[1]] != ds.parent[curr[2]]){
            ds.set_union(curr[1], curr[2]);
            out.add(Array<int, 3>(curr[0], min(curr[1], curr[2]), max(curr[1], curr[2])));
            cost += curr[0];
        }
    }
    
    while (out.size() > 0){
        auto curr = out.top();
        out.pop();
        cout << curr[1] << " " << curr[2] << " " << curr[0] << endl;
    }
    cout << cost << endl;


    return 0;
}