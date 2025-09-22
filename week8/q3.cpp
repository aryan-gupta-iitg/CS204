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
                return T();
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

    string s;
    cin >> s;

    int mxsz = 0;

    Stack<double> st;
    int n = s.size();
    int sz = 0;
    for (int i=0;i<n;i++){
        if (s[i] >= '0' && s[i] <= '9'){
            st.push(s[i]-'0');
            sz++;
            mxsz = max(mxsz, sz);
        }else{
            if (sz < 2){
                cout << "Invalid" << endl;return;
            }
            sz--;
            int f = st.top();st.pop();
            int l = st.top();st.pop();
            if (s[i]=='+'){
                st.push(f+l);
            }else if (s[i] == '-'){
                st.push(f-l);
            }else if (s[i] == '*'){
                st.push(f*l);
            }else{
                st.push(f/l);
            }
        }
    }

    return 0;
}