#include <iostream>
#include "../templates/ds.cpp"

using namespace std;

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

Vector<Pair<int, int> > poss;

void dfs(int i, int j, Vector<Vector<int> > & vis, int & n, int & m, Vector<Vector<int> > & grid){
    vis[i][j] = 1;
    for (int l=0;l<poss.size();l++){
        Pair<int, int> nxt(poss[l].first + i, poss[l].second + j);
        if (((nxt.first >= 0 && nxt.first < n) && (nxt.second >= 0 && nxt.second < m)) && (!vis[nxt.first][nxt.second] && grid[nxt.first][nxt.second] == 1)){
            dfs(nxt.first, nxt.second, vis, n, m, grid);
        }
    }
}

int main(){
    poss.push_back(Pair<int,int>(-1, 0));
    poss.push_back(Pair<int,int>(0, -1));
    poss.push_back(Pair<int,int>(1, 0));
    poss.push_back(Pair<int,int>(0, 1));

    int n, m;
    cin >> n >> m;

    Vector<Vector<int> > grid(n, Vector<int>(m, 0));
    Vector<Vector<int> > vis(n, Vector<int>(m, 0));

    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            int x;
            cin >> x;
            grid[i][j] = x;
        }
    }
    int ans = 0;
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            if (!vis[i][j] && grid[i][j] == 1){
                dfs(i, j, vis, n, m, grid);
                ans++;
            }
        }
    }

    cout << ans << endl;

    return 0;
}