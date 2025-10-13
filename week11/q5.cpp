#include <iostream>
#include <sstream>
using namespace std;

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
            if (afterwhich == nullptr) return;
            node * nw = new node(val);
            nw->pre = afterwhich;
            nw->nxt = afterwhich->nxt;
            afterwhich->nxt = nw;
            if (nw->nxt == nullptr){
                end = nw;
            } else {
                nw->nxt->pre = nw;
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

template<class T>
class chainHash{
    int (*hf)(T & a);
    struct hashNode{
        int val;
        T key;
    };
    typedef struct hashNode hashNode;
    LLst<hashNode> * tbl;
    int m;
    int zero = 0;
    public:
        chainHash(int (* hash_func)(T & a), int m = 100003){
            this->m = m;
            this->hf = hash_func;
            this->tbl = new LLst<hashNode>[m];
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
        
        int& operator[](T key){
            hashNode * pos = search(key);
            if (pos == nullptr){
                hashNode newNode;
                newNode.key = key;
                newNode.val = 0;
                int hashPos = (hf(key))%m;
                (tbl + hashPos)->push(newNode);
                pos = search(key);
            }
            return pos->val;
        }
};

int rollingHash(string & s){
    const int M = 1e9 + 7;
    int x = 1;
    int ans = 0;
    for (int i=0;i<s.size();i++){
        ans += x * (s[i]-'a'+1);
        ans %= M;
        x *= 31;
        x %= M;
    }
    return ans;
}

int main(){

    string para;
    getline(cin, para, '#');

    for (auto & ele: para){
        if (ele == '.' || ele == ',' || ele == ';' || ele == ':' || ele == '?' || ele == '!'){
            ele = ' ';
        }else if (ele >= 'A' && ele <= 'Z'){
            ele -= 'A'-'a';
        }
    }

    stringstream ss(para);

    chainHash<string> ch(rollingHash);
    chainHash<string> hinv(rollingHash);

    string token;
    while (1){
        cin >> token;
        if (token == "#") break;
        hinv[token] = 1;
    }
    token = "";
    int ans = 0;
    string arr[2*(10000)];
    int i = 0;
    cout << para << endl;
    while (getline(ss, token, ' ')){
        if (hinv[token] != 1 && token.length() > 0){
            ch[token]++;
            ans = max(ans, ch[token]);
            arr[i++] = token;
        }
    }
    
    for (int j=0;j<i;j++){
        if (ch[arr[j]] == ans){
            cout << arr[j] << endl;return 0;
        }
    }
    
    return 0;
}