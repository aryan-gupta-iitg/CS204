#include <iostream>

using namespace std;

template <class T>
class Stack{
    T * arr;
    int i;
    int MX_SIZE;
    const int INF = 1e9+7;
    public:
        Stack(int MX_SIZE = 1000000){
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

        void insertMin(int m){
            i++;
            arr[i] = m;
            int t = m;
            int j = i-1;
            while (j >= 0 && arr[j] < t){
                arr[j+1] = arr[j];
                j--;
            }
            arr[j+1] = t;
        }
};

int main(){

    int n;
    cin >> n;
    Stack<int> st;
    for (int i=0;i<n;i++){
        int t;
        cin >> t;
        if (t == 1){
            int m;
            cin >> m;
            st.insertMin(m);
        }else if (t == 2){
            if (st.isempty()){
                cout << -1 << endl;
            }else{
                cout << st.top() << endl;
            }
        }else{
            if (!st.isempty()){
                st.pop();
            }
        }
    }

    return 0;
}