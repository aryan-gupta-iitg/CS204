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
            if (i > 0){
                premin[i] = min(arr[i], premin[i-1]);
            }else{
                premin[i] = arr[i];
            }
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

int imp[300];

string to_postfix(string s){
    string out;
    Stack<char> st;
    int n = s.size();
    for (int i=0;i<n;i++){
        if (s[i] >= 'a' && s[i] <= 'z'){
            out.push_back(s[i]);
        }else if (s[i] == ')'){
            while (!st.isempty() && st.top() != '('){
                out.push_back(st.top());
                st.pop();
            }
            if (st.top() == '('){st.pop();}
        }else{ 

            while (st.isempty() || imp[st.top()] > imp[s[i]]){
                out.push_back(st.top());
                st.pop();
            }
            st.push(s[i]);
        }
    }
    while (!st.isempty()){
        out.push_back(st.top());
        st.pop();
    }
}

int main(){
    imp['('] = 0;
    imp['+'] =  1;
    imp['-'] = 1;
    imp['*'] = 2;
    imp['/'] = 2;
    string s;
    cin >> s;
    string pf = to_postfix(s);
    cout << pf << endl;
}