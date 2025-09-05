#include <iostream>

using namespace std;

template <class T>
class LLst{
    class node{
        public:
            T val;
            node * nxt;
            node * pre;
            node(T val){
                this->val = val;
            }
    };

    // void rev(node * curr, node * par){
    //     if (curr->nxt != nullptr){
    //         rev(curr->nxt, curr);
    //     }
    //     curr->pre = curr->nxt;
    //     curr->nxt = par;
    // }

    int sz = 0;
    public:
        node * head = nullptr;
        node * end = nullptr;
        LLst(){}
        void push(T nd){
            node * nw = new node(nd);
            nw->nxt = nullptr;
            nw->pre = end;
            if (end != nullptr){
                end->nxt = nw;
            }
            end = nw;
            if (head == nullptr){
                this->head = nw;
            }
            sz++;
        }
        int size(){
            return sz;
        }
        void pop_back(){
            if (head == nullptr){return;}
            sz -= 1;
            node * tmp = end;
            end = end->pre;
            if (end != nullptr) end->nxt = nullptr;
            if (end == nullptr) head = nullptr;
            delete tmp;
        }

        void pop_front(){
            if (head == nullptr){return;}
            sz -= 1;
            node * tmp = head;
            head = head->nxt;
            if (head != nullptr) head->pre = nullptr;
            if (head == nullptr) end = nullptr;
            delete tmp;
        }

        void insert(node * afterwhich, T val){
            node * nw = new node(val);
            nw->pre = afterwhich;
            nw->nxt = afterwhich->nxt;
            afterwhich->nxt = nw;
            if (nw->nxt == nullptr){
                end = nw;
            }
            sz += 1;
        }

        void erase(node * which){
            if (which == nullptr) return;
            if (which->pre == nullptr && which->nxt == nullptr){
                head = nullptr;
                end = nullptr;
                sz -= 1;
            }else if (which->nxt == nullptr){
                pop_back();
            }else if (which->pre == nullptr){
                pop_front();
            }else{
                which->pre->nxt = which->nxt;
                which->nxt->pre = which->pre;
                delete which;
                sz -= 1;
            }
        }

        void insertionSort(bool (*comp)(T & a, T & b)){
            auto i = this->head;
            if (head != nullptr){
                i = i->nxt;
                if (i == nullptr) return;
            }else{
                return;
            }
            while (i != nullptr){
                auto j = i;
                while (j->pre != nullptr){
                    if (!comp(j->pre->val, j->val)){
                        swap(j->pre->val, j->val);
                        j = j->pre;
                    }else{
                        break;
                    }
                }
                i = i->nxt;
            }
        }
        // void reverse(node * from){
        //     rev(from, nullptr);
        //     if (from == this->head){
        //         node * tmp = head;
        //         head = end;
        //         end = tmp;
        //     }
        // }
};

// template <>
// class LLst<int>{
//     public:
//         void show(){
//             auto curr = this->head;
//             while (curr != nullptr){
//                 cout << curr->val << " ";
//             }cout << endl;
//         }
// };

bool comp(int & a, int & b){
    return a < b;
}

int main(){
    int n;
    cin >> n;

    LLst<int> ll;
    for (int i=0;i<n;i++){
        int x;
        cin >> x;
        ll.push(x);
    }
    ll.insertionSort(comp);

    auto curr = ll.head;
    while (curr != nullptr){
        cout << curr->val << " ";
        curr = curr->nxt;
    }cout << endl;
    return 0;
}