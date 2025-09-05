#include <bits/stdc++.h>
#include "../templates/ds.cpp"
using namespace std;

int main(){

    LLst<int> ll;
    ll.push(46);
    ll.push(4623);
    ll.push(4613);
    ll.push(446);
    
    auto head = ll.head;
    
    while (head != NULL){
        cout << head->val << " ";
        head = head->nxt;
    }cout << endl;

    ll.pop_back();
    head = ll.head;
    while (head != NULL){
        cout << head->val << " ";
        head = head->nxt;
    }cout << endl;
    ll.reverse();
    head = ll.head;
    while (head != NULL){
        cout << head->val << " ";
        head = head->nxt;
    }cout << endl;

    return 0;
}