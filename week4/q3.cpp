#include <bits/stdc++.h>
#include "../templates/ds.cpp"
using namespace std;

struct patient{
    string name;
    int s, t;
};

typedef struct patient pat;

bool comp(pat & a, pat & b){
    if (a.s == b.s){
        return a.t > b.t;
    }else{
        return a.s < b.s;
    }
}

int main(){

    Heap<pat> hp(1000, comp);
    
    while (1){
        string typ;
        cin >> typ;
        if (typ == "EXIT"){break;}
        else if (typ == "ADD"){
            string name;
            cin >> name;
            int s, t;
            cin >> s >> t;
            pat p = {name, s, t};
            hp.add(p);
        }else if (typ == "SERVE"){
            cout << hp.top().name << endl;
            hp.pop();
        }else{
            hp.show();
        }
    }

    return 0;
}