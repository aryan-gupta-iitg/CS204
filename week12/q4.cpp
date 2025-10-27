#include <bits/stdc++.h>

using namespace std;

template <class T>
class Vector{
    int sz;
    T * arr;
    int mx;
    bool _init = 0;
    void expand(){
        int newsize = 2*this->mx;
        if (newsize == 0) newsize = 1;
        T * tmp = new T[newsize]();
        for (int i=0;i<this->sz;i++){
            tmp[i] = arr[i];
        }
        delete[] this->arr;
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

void dfs(int v, Vector<int> & col, Vector<int> & vis, int & n, int & m, Vector<Vector<int> > & graph, bool & bip){
    vis[v] = 1;
    for (int i=0;i<graph[v].size();i++){
        auto ele = graph[v][i];
        cout << v << " " << ele << endl;

        if (col[ele] == -1){ // If neighbor is not colored
            col[ele] = 1 - col[v]; // Color it with the opposite color
            dfs(ele, col, vis, n, m, graph, bip);
            if (!bip) return; // Early exit if a conflict is found in recursion
        }
        // If neighbor is already colored, check for conflict
        else if (col[ele] == col[v]){ 
            bip = false; // Conflict: same color, not bipartite
            return;
        }
    }

}

int main(){
    int n, m;
    cin >> n >> m;

    Vector<Vector<int> > graph(n+1);
    Vector<int> vis(n+1, 0);

    for (int i=0;i<m;i++){
        int u, v;
        cin >> u >> v;
        graph[u].push(v);
        graph[v].push(u);
    }
    Vector<int> col(n+1, -1);
    bool bip = 1;
    for (int i=1;i<=n;i++){
        if (!vis[i]){
            col[i] = 1;
            dfs(i, col, vis, n, m, graph, bip);
        }
    }

    cout << (bip?"YES":"NO") << endl;

    return 0;
}