#include <iostream>

using namespace std;

struct node{
    int val;
    struct node * nxt;
    int ind;
};
typedef struct node node;

int main(){

    int n;
    cin >> n;
    
    node * head = nullptr;
    node * lst = nullptr;
    for (int i=0;i<n;i++){
        int x;
        cin >> x;
        if (head == nullptr){
            head = new node();
            head->ind = i+1;
            head->val = x;
            head->nxt = head;
            lst = head;
        }else{
            node * tmp = new node();
            tmp->ind = i+1;
            lst->nxt = tmp;
            tmp->val = x;
            tmp->nxt = head;
            lst = tmp;
        }
    }
    
    auto curr = head;
    auto bef = lst;
    int k;cin >> k;
    int sz = n;
    while (sz > 0){
        if (curr->val > k){
            curr->val -= k;
            cout << "P" << curr->ind << " ";
            bef = curr;
            curr = curr->nxt;
            // cout << curr->val << endl;
        }else{
            cout << "P" << curr->ind << " ";
            if (sz == 1){delete curr;break;}
            bef->nxt = curr->nxt;
            node * tmp = curr;
            curr = curr->nxt;
            delete tmp;
            sz -= 1;
        }
    }cout << endl;
    return 0;
}