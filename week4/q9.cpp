#include <iostream>

using namespace std;

struct stud{
    string id;
    string course;
    int time;
    int year;
};
typedef struct stud stud;

int gettime(string s){
    int h = stoi(s.substr(0, 2));
    int m = stoi(s.substr(3, 2));
    return 60*h + m;
}

bool comp(stud & a, stud & b){
    if (a.time == b.time){
        return a.year > b.year;
    }else{
        return a.time < b.time;
    }
}

template<class T>
void merge(T * a, int l, int mid, int h, bool (*comp)(T & a, T & b)){
    int n1 = mid - l + 1;
    int n2 = h-mid;
    T left[n1];
    T right[n2];
    for (int i=0;i<n1;i++){
        left[i] = a[l+i];
    }
    for (int i=0;i<n2;i++){
        right[i] = a[mid+1+i];
    }

    int i = 0;
    int j = 0;
    for (int p=l;p<=h;p++){
        if (i < n1 && j < n2){
            if (comp(left[i], right[j])){
                a[p] = left[i++];
            }else{
                a[p] = right[j++];
            }
        }else if (i < n1){
            a[p] = left[i++];
        }else{
            a[p] = right[j++];
        }
    }
}

template <class T>
void mergesort(T * a, int l, int h, bool (*comp)(T &a, T&b)){
    if (l >= h)return;
    int mid = (h+l)/2;
    mergesort<T>(a, l, mid, comp);
    mergesort<T>(a, mid+1, h, comp);
    merge<T>(a, l, mid, h, comp);
}

bool cmp1(string & a, string & b){
    return a < b;
}

int main(){

    int r, c;
    cin >> r >> c;
    stud a[r];
    string courses[r];
    for (int i=0;i<r;i++){
        string id;
        string course;
        string time;
        int year;
        cin >> id >> course >> time >> year;
        courses[i] = course;
        a[i] = {id, course, gettime(time), year};
    }

    mergesort<stud>(a, 0, r-1, comp);
    mergesort<string>(courses, 0, r-1, cmp1);

    int j = 0;
    int done = 0;
    while (j < r){
        int taken = 0;
        cout << courses[j] << ": ";
        string crs = courses[j];
        for (int i=0;i<r;i++){
            if (taken >= c){break;}
            if (a[i].course == courses[j]){
                taken += 1;
                cout << a[i].id << " ";
            }
        }cout << endl;
        done += taken;
        while (j < r && courses[j]==crs) j++;
    }

    cout << "Students not enrolled: " << (r-done) << endl;
    return 0;
}