#include <iostream>
// Status - DONE !
using namespace std;
const int INF = 1e9;
struct node{
    int val;
    struct node * right=nullptr;
    struct node * left=nullptr;
};

typedef struct node node;

template<class T>
class quickSort{
    int n;
    bool (*comp)(T & a, T & b);
    T * a;
    
    public:
        int partition(int l, int h){
            int p = h;

            int i=l-1;
            for (int j=l;j<h;j++){
                if (comp(a[j], a[p])){
                    swap(a[++i], a[j]);
                }
            }
            swap(a[++i], a[p]);
            return i;
        }
        void sort(int l, int r){
            if (l >= r){
                return;
            }
            int i = partition(l, r);
            sort(l, i-1);
            sort(i+1, r);
        }
        quickSort(int n, T * a, bool (* comp)(T & a, T & b)){
            this->a = a;
            this->n = n;
            this->comp = comp;
        }
};

void makeBST(int l, int h, node * & root, int * a){
    if (l > h){
        return;
    }
    int mid = (l+h)/2;
    root = (node *) malloc(sizeof(node));
    root->val = a[mid];
    makeBST(mid + 1, h, (root)->right, a);
    makeBST(l, mid-1, (root)->left, a);
}

node * BSTSearch(node * & root, int v){

    if (root == nullptr){return nullptr;}
    if (root->val == v){return root;}
    if (root->val < v){
        return BSTSearch(root->right, v);
    }else{
        return BSTSearch(root->left, v);
    }
}

node * BSTFindLCA(node * & root, int v1, int v2){
    if (v1 > root->val && v2 > root->val){
        return BSTFindLCA(root->right, v1, v2);
    }else if (v1 < root->val && v2 < root->val){
        return BSTFindLCA(root->left, v1, v2);
    }else{
        return root;
    }
}

node * BSTInsert(node * & root, int v){
    if (root == nullptr){
        root = (node *) malloc(sizeof(node));
        root->val = v;
        return root;
    }
    if (root->val > v){
        return BSTInsert((root->left), v);
    }else{
        return BSTInsert((root->right), v);
    }
}

void BSTInorder(node * root){
    if (root == nullptr) return;
    BSTInorder(root->left);
    cout << root->val << " ";
    BSTInorder(root->right);
}

int main(){

    int n;
    cin >> n;

    node * root = nullptr;
    for (int i=0;i<n;i++){
        int x;
        cin >> x;
        BSTInsert(root, x);
    }

    BSTInorder(root);
    cout << endl;

    return 0;
}