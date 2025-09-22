#include <iostream>
#include <cstdlib>

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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    if (!(cin >> n)) return 0;

    Stack<int> A(n + 5), B(n + 5), C(n + 5);
    for (int d = (int)n; d >= 1; --d) A.push(d);

    auto moveBetween = [](Stack<int>& s1, Stack<int>& s2, char name1, char name2){
        if (s1.isempty()){
            int d2 = s2.top();
            s2.pop();
            s1.push(d2);
            std::cout << d2 << ' ' << name2 << ' ' << name1 << '\n';
        } else if (s2.isempty()){
            int d1 = s1.top();
            s1.pop();
            s2.push(d1);
            std::cout << d1 << ' ' << name1 << ' ' << name2 << '\n';
        } else if (s1.top() < s2.top()){
            int d1 = s1.top();
            s1.pop();
            s2.push(d1);
            std::cout << d1 << ' ' << name1 << ' ' << name2 << '\n';
        } else {
            int d2 = s2.top();
            s2.pop();
            s1.push(d2);
            std::cout << d2 << ' ' << name2 << ' ' << name1 << '\n';
        }
    };

    long long totalMoves = (1LL << n) - 1;
    if (n % 2 == 1){
        for (long long mv = 1; mv <= totalMoves; ++mv){
            if (mv % 3 == 1) moveBetween(A, C, 'A', 'C');
            else if (mv % 3 == 2) moveBetween(A, B, 'A', 'B');
            else moveBetween(B, C, 'B', 'C');
        }
    } else {
        for (long long mv = 1; mv <= totalMoves; ++mv){
            if (mv % 3 == 1) moveBetween(A, B, 'A', 'B');
            else if (mv % 3 == 2) moveBetween(A, C, 'A', 'C');
            else moveBetween(B, C, 'B', 'C');
        }
    }

    return 0;
}