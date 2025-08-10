#include <iostream>
#include "../include/utils.h"

using namespace std;

int main(){

    int a = 50;
    int b = 79;
    cout << a << " " << b << endl;
    swap(&a, &b);
    cout << a << " " << b << endl;

    return 0;
}