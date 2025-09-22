#include <iostream>

using namespace std;

template <class T>
class Stack{
    T * arr;
    int i;
    int MX_SIZE;
    const int INF = 1e9+7;
    public:
        Stack(int MX_SIZE = 100000){
            this->MX_SIZE = MX_SIZE;
            i = -1;
            arr = (T *) malloc(MX_SIZE * (sizeof(T)));
        }
        bool isempty(){
            return i == -1;
        }

        bool isfull(){
            return i == MX_SIZE-1;
        }
        T top(){
            if (isempty()){
                return T();  // Return default value for type T
            }
            return arr[i];
        }
        void push(T x){
            if (isfull()){
                return;
            }
            arr[++i] = x;
        }

        void pop(){
            if (isempty()){
                return;
            }
            i--;
        }
};


int main(){
    Stack<int> f, s;
    int n;
    cin >> n;
    int sz = 0;
    for (int i=0;i<n;i++){
        int x;
        cin >> x;
        if (x == 1){
            int val;
            cin >> val;
            s.push(val);
            sz++;
        }else{
            if (sz == 0){
                cout << -1 << endl;
            }else{
                if (f.isempty()){
                    while (!s.isempty()){
                        f.push(s.top());
                        s.pop();
                    }
                }
                cout << f.top() << endl;
                f.pop();
                sz--;
            }
        }
    }
}