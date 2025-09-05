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
    //     if (curr->nxt != NULL){
    //         rev(curr->nxt, curr);
    //     }
    //     curr->pre = curr->nxt;
    //     curr->nxt = par;
    // }

    int sz = 0;
    public:
        node * head = NULL;
        node * end = NULL;
        LLst(){}
        void push(T nd){
            node * nw = new node(nd);
            nw->nxt = NULL;
            nw->pre = end;
            if (end != NULL){
                end->nxt = nw;
            }
            end = nw;
            if (head == NULL){
                this->head = nw;
            }
            sz++;
        }
        int size(){
            return sz;
        }
        void pop_back(){
            if (head == NULL){return;}
            sz -= 1;
            node * tmp = end;
            end = end->pre;
            if (end != NULL) end->nxt = NULL;
            if (end == NULL) head = NULL;
            delete tmp;
        }

        void pop_front(){
            if (head == NULL){return;}
            sz -= 1;
            node * tmp = head;
            head = head->nxt;
            if (head != NULL) head->pre = NULL;
            if (head == NULL) end = NULL;
            delete tmp;
        }

        void insert(node * afterwhich, T val){
            node * nw = new node(val);
            nw->pre = afterwhich;
            nw->nxt = afterwhich->nxt;
            afterwhich->nxt = nw;
            if (nw->nxt == NULL){
                end = nw;
            }
            sz += 1;
        }

        void erase(node * which){
            if (which == NULL) return;
            if (which->pre == NULL && which->nxt == NULL){
                head = NULL;
                end = NULL;
                sz -= 1;
            }else if (which->nxt == NULL){
                pop_back();
            }else if (which->pre == NULL){
                pop_front();
            }else{
                which->pre->nxt = which->nxt;
                which->nxt->pre = which->pre;
                delete which;
                sz -= 1;
            }
        }

        void insertionSort(bool (*comp)(T & a, T & b)){
            if (sz == 1) return;
            auto curr = head->nxt;

            
        }

        // void reverse(node * from){
        //     rev(from, NULL);
        //     if (from == this->head){
        //         node * tmp = head;
        //         head = end;
        //         end = tmp;
        //     }
        // }
};

typedef struct node{
    int o[4];
};



int main(){

    LLst<node> ll;
    
    while (1){
        string s;
        cin >> s;
        if (s == "#") break;
        
        string tmp;
        node n;
        int j = 0;
        for (auto & ele: s){
            if (ele != '.'){
                tmp.push_back(ele);
                n.o[j++] = stoi(tmp);
                tmp = "";
            }
        }
        n.o[j++] = stoi(tmp);
        tmp = "";
        ll.push(n);
        

    }




    
    return 0;
}