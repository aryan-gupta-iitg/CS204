#include <iostream>

using namespace std;

int main(){

    int h[257];
    for (int i=0;i<257;i++){
        h[i]=0;
    }

    h['I'] = 1;
    h['V'] = 5;
    h['X'] = 10;
    h['L'] = 50;
    h['C'] = 100;
    h['D'] = 500;
    h['M'] = 1000;

    string s;
    cin >> s;
    int val = 0;
    for (int i=0;i<s.size();i++){
        if (i < s.size()-1 && h[s[i+1]] > h[s[i]]){
            val += h[s[i+1]] - h[s[i]];
            i++;
        }else{
            val += h[s[i]];
        }
    }

    cout << val << endl;

    return 0;
}
