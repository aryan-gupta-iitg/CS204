#include <iostream>

using namespace std;
const int INF = 1e9;
struct node{
    int val;
    struct node * right=nullptr;
    struct node * left=nullptr;
};

typedef struct node node;

void dfs(node * v, int lower, int upper, bool & poss){
    if (lower > upper){
        poss = 0;return;
    }
    if (!(v->val >= lower && v->val <= upper)){
        poss = 0;
        return;
    }
    
    if (v->right != nullptr){
        dfs(v->right, max(lower, v->val), upper, poss);
    }
    if (v->left != nullptr){
        dfs(v->left, lower, min(upper, v->val), poss);
    }
}

int main(){

    int n;
    cin >> n;

    int a[2*n+1];
    node tree[2*n+1];
    int j = 1;
    int i = 1;
    node * root;
    while (i <= n){
        int x;
        cin >> x;
        if (x == -1){
            int par = j/2;
            if (j == 2*par){
                tree[par].left = nullptr;
            }else{
                tree[par].right = nullptr;
            }
        }else{
            tree[j].val = x;
            int par = j/2;
            if (par < 1){
                root = &tree[j];
            }
            if (j == 2*par){
                tree[par].left = &tree[j];
            }else{
                tree[par].right = &tree[j];
            }
            i++;
        }
        j++;
    }
    bool poss = 1;
    dfs(root, -INF, INF, poss);
    cout << (poss?"T":"F") << endl;
    return 0;
}