#include <iostream>

using namespace std;

int main(){

    int hsh[257];
    for (int i=0;i<257;i++){
        hsh[i] = 0;
    }

    string s;
    cin >> s;
    int i = 0;
    int j = 1;

    hsh[s[i]] = 1;
    int ans = 1;

    while (j < s.size()){
        if (hsh[s[j]] > 0){
            hsh[s[i++]]--;
        }else{
            hsh[s[j++]]++;
        }
        ans = max(ans, j-i);
    }

    cout << ans << endl;

    return 0;
}