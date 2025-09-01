#include <bits/stdc++.h>

using namespace std;

template <class T>
class Heap{
    T * hp;

    int par(int curr)
    {
        return curr / 2;
    }

    int lch(int curr)
    {
        return 2 * curr;
    }
    int rch(int curr)
    {
        return 2 * curr + 1;
    }

    bool (*comp)(T &a, T &b);
    int sz;
    int n;
    public:
        Heap(int n, bool (*comp)(T & a, T & b)){
            this->hp = (T *) malloc(sizeof(T) * (n+1));
            this->comp = comp;
            this->sz = 0;
            this->n = n;
        }

        ~Heap(){
            free(this->hp);
            this->hp = NULL;
        }

        void add(T nw){
            if (this->sz >= this->n){return;}
            hp[++sz] = nw;
            int curr = sz;
            auto & heap = hp;
            while (par(curr) >= 1 && comp(heap[par(curr)], heap[curr]))
            {
                swap(heap[par(curr)], heap[curr]);
                curr = par(curr);
            }
        }

        void pop(){
            if (this->sz <= 0) return;
            int & e = sz;
            auto & heap = hp;
            swap(heap[1], heap[(e--)]);
            int curr = 1;
            while (1)
            {
                int left = lch(curr);
                int right = rch(curr);
                if (left > e && right > e)
                {
                    break;
                }
                else if (left > e)
                {
                    int c3 = comp(heap[curr], heap[right]);
                    if (!c3)
                        break;
                    swap(heap[curr], heap[right]);
                    curr = right;
                }
                else if (right > e)
                {
                    int c2 = comp(heap[curr], heap[left]);
                    if (!c2)
                        break;
                    swap(heap[curr], heap[left]);
                    curr = left;
                }
                else
                {
                    int c1 = comp(heap[left], heap[right]);
                    int c2 = comp(heap[curr], heap[left]);
                    int c3 = comp(heap[curr], heap[right]);
                    if (c1)
                    {
                        if (!c3)
                            break;
                        swap(heap[curr], heap[right]);
                        curr = right;
                    }
                    else
                    {
                        if (!c2)
                            break;
                        swap(heap[curr], heap[left]);
                        curr = left;
                    }
                }
            }
        }

        T top(){
            return this->hp[1];
        }
    
        void show(){
            int e = this->sz;
            auto & heap = this->hp;
            while (e > 1)
            {
                swap(heap[1], heap[(e--)]);
                int curr = 1;
                while (1)
                {
                    int left = lch(curr);
                    int right = rch(curr);
                    if (left > e && right > e)
                    {
                        break;
                    }
                    else if (left > e)
                    {
                        int c3 = comp(heap[curr], heap[right]);
                        if (!c3)
                            break;
                        swap(heap[curr], heap[right]);
                        curr = right;
                    }
                    else if (right > e)
                    {
                        int c2 = comp(heap[curr], heap[left]);
                        if (!c2)
                            break;
                        swap(heap[curr], heap[left]);
                        curr = left;
                    }
                    else
                    {
                        int c1 = comp(heap[left], heap[right]);
                        int c2 = comp(heap[curr], heap[left]);
                        int c3 = comp(heap[curr], heap[right]);
                        if (c1)
                        {
                            if (!c3)
                                break;
                            swap(heap[curr], heap[right]);
                            curr = right;
                        }
                        else
                        {
                            if (!c2)
                                break;
                            swap(heap[curr], heap[left]);
                            curr = left;
                        }
                    }
                }
            }
            reverse(this->hp+1, this->hp + sz + 1);
            for (int i=1;i<=sz;i++){
                cout << this->hp[i].name << " ";
            }cout << endl;
        }
};

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

        // void reverse(node * from){
        //     rev(from, NULL);
        //     if (from == this->head){
        //         node * tmp = head;
        //         head = end;
        //         end = tmp;
        //     }
        // }
};

template <class T>
class circularLinkedList{
    class node{
        public:
            T val;
            node * nxt;
            node * pre;
            node(T val){
                this->val = val;
            }
    };
    int sz = 0;
    public:
        node * head = nullptr;
        circularLinkedList(){}
        int size(){
            return sz;
        }

        void push(T val){
            sz += 1;
            if (head == nullptr){
                node * nw = new node(val);
                this->head = nw;
                this->head->nxt = this->head;
                this->head->pre = this->head;
                return;
            }
            node * nw = new node(val);
            
            head->pre->nxt = nw;
            nw->nxt = head;
            nw->pre = head->pre;
            head->pre = nw;
        }

        void insert(T val, node * afterwhich=nullptr){
            sz += 1;
            if (afterwhich == nullptr) afterwhich = this->head;
            if (afterwhich == nullptr){
                node * nw = new node(val);
                this->head = nw;
                this->head->nxt = this->head;
                this->head->pre = this->head;
                return;
            }
            cout << "here" << endl;
            node * nw = new node(val);
            nw->pre = afterwhich;
            nw->nxt = afterwhich->nxt;
            afterwhich->nxt = nw;
        }

        void erase(node * which){
            if (which == nullptr) return;
            if (sz == 1){
                delete which;
                this->head = nullptr;
                sz -= 1;
            }else{
                which->pre->nxt = which->nxt;
                which->nxt->pre = which->pre;
                delete which;
                sz -= 1;
            }
        }

};
