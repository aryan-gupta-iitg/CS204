#include <bits/stdc++.h>
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


template <class T>
class Vector{
    int sz;
    T * arr;
    int mx;
    bool _init = 0;
    void expand(){
        int newsize = 2*this->mx;
        T * tmp = new T[newsize];
        for (int i=0;i<this->mx;i++){
            tmp[i] = arr[i];
        }
        delete this->arr;
        this->arr = tmp;
        this->mx = newsize;
    }

    public:
        Vector(int sz = 0, T def = T{}){
            this->mx = 1;
            if (sz > 0) this->mx = 1<<((int)(ceil(log2(sz))));
            this->arr = new T[this->mx];
            for (int i=0;i<this->mx;i++){
                this->arr[i] = def;
            }
            this->sz = sz;
        }

        Vector(const Vector<T>& other) 
            : sz(other.sz), mx(other.mx) {
            // std::cout << "Copy constructor called" << std::endl; // For debugging
            arr = new T[mx];
            // Copy all elements from the other array
            for (int i = 0; i < sz; i++){ // Only need to copy 'sz' elements
                arr[i] = other.arr[i];
            }
        }

        Vector<T>& operator=(const Vector<T>& other){
            // std::cout << "Copy assignment called" << std::endl; // For debugging

            // 1. Check for self-assignment
            if (this == &other) {
                return *this;
            }

            // 2. Free old memory
            delete[] arr;

            // 3. Copy scalar members
            sz = other.sz;
            mx = other.mx;

            // 4. Allocate new memory and copy data
            arr = new T[mx];
            for (int i = 0; i < sz; i++){
                arr[i] = other.arr[i];
            }

            // 5. Return self-reference
            return *this;
        }
        
        void push_back(){
            // base case, does nothing.
        }
        
        template <typename... Args>
        void push_back(T val, Args... args){
            push(val);
            push_back(args...);
        }
        
        bool full(){
            return (this->sz == this->mx);
        }

        bool empty(){
            return (this->sz == 0);
        }
        
        T push(T val){
            if (this->full()){
                expand();
            }
            this->arr[this->sz++] = val;
            return val;
        }

        T pop_back(){
            if (this->empty()){
                return T{};
            }else{
                this->sz--;
                return arr[this->sz];
            }
        }

        T & operator[](int ind){
            if (ind < 0){
                throw "Index should be atleast 0 !";
            }
            if (ind < this->mx){
                return this->arr[ind];
            }else{
                throw "Out of range !";
            }
        }

        int size(){
            return this->sz;
        }

        ~Vector(){
            delete[] this->arr;
        }
};

template <class F, class S>
class Pair{
    public:
        F first;
        S second;
        Pair() : first(F{}), second(S{}) {}
        Pair(F first, S second){
            this->first = first;
            this->second = second;
        }
};
const int INF = 1e9+7;

bool comp(Pair<int,int> & a, Pair<int,int> & b){
    if (a.first == b.first){
        return a.second > b.second;
    }else{
        return a.first > b.first;
    }
}

int main(){

    int n, m;
    cin >> n >> m;
    Vector<Pair<Pair<int,int>, int> > edges(m);

    for (int i=0;i<m;i++){
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = Pair<Pair<int, int>,int>({Pair<int,int>({u, v}), w});
    }
    Vector<int> d(n, INF);
    int x;
    cin >> x;
    d[x] = 0;
    for (int j=0;j<n-1;j++){
        bool didrelax = 0;
        for (int i=0;i<m;i++){
            int u = edges[i].first.first;
            int v = edges[i].first.second;
            int w = edges[i].second;
            if (d[u] + w < d[v]){
                d[v] = d[u] + w;
                didrelax = 1;
            }
        }   
        if (!didrelax){
            break;
        }
    }

    for (int i=0;i<n;i++){
        cout << i << " " << d[i] << endl;
    }

    


    return 0;
}