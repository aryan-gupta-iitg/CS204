#include <iostream>

using namespace std;

template <class T>
class Stack{
    T * arr;
    int * premin;
    int i;
    int MX_SIZE;
    const int INF = 1e9+7;
    public:
        Stack(int MX_SIZE = 100000){
            this->MX_SIZE = MX_SIZE;
            i = -1;
            premin = (int *) malloc(MX_SIZE * sizeof(int));
            for (int i=0;i<MX_SIZE;i++){
                premin[i] = INF;
            }

            arr = (T *) malloc(MX_SIZE * (sizeof(T)));
        }
        bool isempty(){
            return i == -1;
        }

        bool isfull(){
            return i == MX_SIZE-1;
        }
        int top(){
            if (isempty()){
                return -INF;
            }
            return arr[i];
        }
        void push(T x){
            if (isfull()){
                return;
            }
            arr[++i] = x;
            premin[i] = min(arr[i], ((i > 0)?premin[i-1]:INF));
        }

        void pop(){
            if (isempty()){
                return;
            }
            arr[i--];
        }

        int getMin(){
            if (isempty()){
                return -INF;
            }
            return premin[i];
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
            int x;
            cin >> x;
            st.push(x);
        }else if (t == 2){
            st.pop();
        }else if (t == 3){
            int x = st.top();
            if (x == -1e9){
                cout << "null" << endl;
            }else{
                cout << x << endl;
            }
        }else{
            int x = st.getMin();
            if (x == -1e9){
                cout << "null" << endl;
            }else{
                cout << x << endl;
            }
        }
    }
    
    return 0;
}