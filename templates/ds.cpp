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
            this->hp = nullptr;
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
    int sz = 0;
    public:
        class node{
            public:
                T val;
                node * nxt;
                node * pre;
                node(T val){
                    this->val = val;
                }
        };
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

        // void reverse(node * from){
        //     rev(from, nullptr);
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

template <class T>
class Stack{
    T * arr;
    // int * premin;
    int i;
    int MX_SIZE;
    public:
        Stack(int MX_SIZE = 100000){
            this->MX_SIZE = MX_SIZE;
            i = -1;
            // premin = new int(MX_SIZE);
            // memset(premin, 1e9+7, sizeof(premin));
            arr = (T *) malloc(MX_SIZE * (sizeof(T)));
        }
        bool empty(){
            return i == -1;
        }

        bool full(){
            return i == MX_SIZE-1;
        }
        T top(){
            if (empty()){
                return T();
            }
            return arr[i];
        }
        int push(T x){
            if (full()){
                return 0;
            }
            arr[++i] = x;
            // premin[i] = min(arr[i], ((i > 0)?premin[i-1]:1e9+7));
            return 1;
        }

        int pop(){
            if (empty()){
                return -1e9;
            }
            return arr[i--];
        }

        // int getMin(){
        //     if (empty()){
        //         return -1e9;
        //     }
        //     return premin[i];
        // }
};

template<class T, class V>
class chainHash{
    V (*hf)(T & a);
    struct hashNode{
        V val;
        T key;
    };
    typedef struct hashNode hashNode;
    LLst<hashNode> * tbl;
    int m;
    V defaultValue;
    public:
        chainHash(int (* hash_func)(T & a), int m = 100003, V defaultVal = V()){
            this->m = m;
            this->hf = hash_func;
            this->tbl = new LLst<hashNode>[m];
            this->defaultValue = defaultVal;
        }
        
        hashNode * search(T & key){
            int pos = (hf(key))%m;
            if ((tbl + pos)->size() == 0){
                return nullptr;
            }
            typename LLst<hashNode>::node* hd = (tbl + pos)->head;
            
            while (hd != nullptr){
                if (hd->val.key == key){
                    break;
                }
                hd = hd->nxt;
            }

            if (hd == nullptr) return nullptr;
            return &hd->val;
        }
        
        V& operator[](T key){
            hashNode * pos = search(key);
            if (pos == nullptr){
                hashNode newNode;
                newNode.key = key;
                newNode.val = defaultValue;
                int hashPos = (hf(key))%m;
                (tbl + hashPos)->push(newNode);
                pos = search(key);
            }
            return pos->val;
        }
        
        V get(T key, V defaultVal = V()) const {
            hashNode * pos = const_cast<chainHash*>(this)->search(key);
            if (pos == nullptr){
                return defaultVal;
            }
            return pos->val;
        }
        
        bool contains(T key) const {
            return const_cast<chainHash*>(this)->search(key) != nullptr;
        }
};

template <class T>
class Queue{
    int sz = 0;
    int l = -1;
    int r = -1;
    int mx;
    T * arr;
    public:
        Queue(int MX=1e5){
            this->mx = MX;
            arr = new T[this->mx];
            l = 0;
            r = 0;
        }

        void print(){
            int j = l+1;
            cout << "Queue: ";
            for (int i=0;i<this->sz;i++){
                cout << this->arr[j++] << " ";
                j %= this->mx;
            }
            cout << endl;
        }

        bool empty(){
            return (this->sz == 0);
        }

        bool full(){
            return (this->sz == this->mx - 1);
        }
        
        T front(){
            if (!this->empty()) return this->arr[l+1];
            throw std::runtime_error("Queue is Empty!");
        }

        T push(T val){
            if (this->full()) throw runtime_error("Queue is full!");
            r = (r+1)%this->mx;
            arr[r] = val;
            this->sz++;
            return val;
        }

        T pop(){
            if (this->empty()) throw std::runtime_error("Queue is Empty!");
            l = (l + 1)%this->mx;
            this->sz--;
            return arr[l];
        }
        int size(){
            return this->sz;
        }
};

template <class T>
class Vector{
    int sz;
    T * arr;
    int mx;
    bool _init = 0;
    void expand(){
        int newsize = 2*this->mx;
        T * tmp = new T[newsize];
        for (int i=0;i<this->mx;i++){
            tmp[i] = arr[i];
        }
        delete this->arr;
        this->arr = tmp;
        this->mx = newsize;
    }

    public:
        Vector(int sz = 0, T def = T{}){
            this->mx = 1;
            if (sz > 0) this->mx = 1<<((int)(ceil(log2(sz))));
            this->arr = new T[this->mx];
            for (int i=0;i<this->mx;i++){
                this->arr[i] = def;
            }
            this->sz = sz;
        }

        Vector(const Vector<T>& other) 
            : sz(other.sz), mx(other.mx) {
            // std::cout << "Copy constructor called" << std::endl; // For debugging
            arr = new T[mx];
            // Copy all elements from the other array
            for (int i = 0; i < sz; i++){ // Only need to copy 'sz' elements
                arr[i] = other.arr[i];
            }
        }

        Vector<T>& operator=(const Vector<T>& other){
            // std::cout << "Copy assignment called" << std::endl; // For debugging

            // 1. Check for self-assignment
            if (this == &other) {
                return *this;
            }

            // 2. Free old memory
            delete[] arr;

            // 3. Copy scalar members
            sz = other.sz;
            mx = other.mx;

            // 4. Allocate new memory and copy data
            arr = new T[mx];
            for (int i = 0; i < sz; i++){
                arr[i] = other.arr[i];
            }

            // 5. Return self-reference
            return *this;
        }
        
        void push_back(){
            // base case, does nothing.
        }
        
        template <typename... Args>
        void push_back(T val, Args... args){
            push(val);
            push_back(args...);
        }
        
        bool full(){
            return (this->sz == this->mx);
        }

        bool empty(){
            return (this->sz == 0);
        }
        
        T push(T val){
            if (this->full()){
                expand();
            }
            this->arr[this->sz++] = val;
            return val;
        }

        T pop_back(){
            if (this->empty()){
                return T{};
            }else{
                this->sz--;
                return arr[this->sz];
            }
        }

        T & operator[](int ind){
            if (ind < 0){
                throw "Index should be atleast 0 !";
            }
            if (ind < this->mx){
                return this->arr[ind];
            }else{
                throw "Out of range !";
            }
        }

        int size(){
            return this->sz;
        }

        ~Vector(){
            delete[] this->arr;
        }
};

template <class F, class S>
class Pair{
    public:
        F first;
        S second;
        Pair() : first(F{}), second(S{}) {}
        Pair(F first, S second){
            this->first = first;
            this->second = second;
        }
};