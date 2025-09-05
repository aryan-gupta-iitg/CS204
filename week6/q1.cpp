#include <iostream>
#include "../templates/ds.cpp"
using namespace std;

int main(){
    int k;
    cin >> k;

    circularLinkedList<int> ll;

    while (1){
        int x;
        cin >> x;
        if (x == -1){break;}
        ll.push(x);
    }

    k %= ll.size();

    for (int i=0;i<k;i++){
        ll.head = ll.head->pre;
    }
    auto curr = ll.head;
    if (ll.size() == 0) cout << -1 << " ";
    for (int i=0;i<ll.size();i++){
        cout << curr->val << " ";
        curr = curr->nxt;
    }cout << endl;

    return 0;
}