#include <iostream>

using namespace std;
template <class T>
class Queue{
    int sz = 0;
    int l = -1;
    int r = -1;
    int mx;
    T * arr;
    public:
        Queue(int MX=1e5){
            this->mx = MX;
            arr = new T[this->mx];
            l = 0;
            r = 0;
        }

        void print(){
            int j = l+1;
            cout << "Queue: ";
            for (int i=0;i<this->sz;i++){
                cout << this->arr[j++] << " ";
                j %= this->mx;
            }
            cout << endl;
        }

        bool empty(){
            return (this->sz == 0);
        }

        bool full(){
            return (this->sz == this->mx - 1);
        }
        
        T front(){
            if (!this->empty()) return this->arr[l+1];
            throw std::runtime_error("Queue is Empty!");
        }

        T push(T val){
            if (this->full()) throw runtime_error("Queue is full!");
            r = (r+1)%this->mx;
            arr[r] = val;
            this->sz++;
            return val;
        }

        T pop(){
            if (this->empty()) throw std::runtime_error("Queue is Empty!");
            l = (l + 1)%this->mx;
            this->sz--;
            return arr[l];
        }
        int size(){
            return this->sz;
        }
};
int adj[21][21];

void bfs(int v, int * vis, int n){
    Queue<int> q(n+1);
    q.push(v);
    vis[v] = 1;
    while (q.size() > 0){
        auto curr = q.front();
        q.pop();
        cout << curr << " ";
        for (int i=0;i<n;i++){
            if (adj[curr][i] && !vis[i]){
                vis[i] = 1;
                q.push(i);
            }
        }
    }
}



int main(){

    int n;
    cin >> n;
    int m;
    cin >> m;

    int vis[n];
    for (int i=0;i<n;i++){
        vis[i] = 0;
    }
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            adj[i][j] = 0;
        }
    }
    for (int i=0;i<m;i++){
        int u, v;
        cin >> u >> v;
        adj[u][v] = 1;
        adj[v][u] = 1;
    }
    
    for (int i=0;i<n;i++){
        if (!vis[i]) bfs(i, vis, n);
    }
    cout << endl;


    return 0;
}