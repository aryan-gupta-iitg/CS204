#include <bits/stdc++.h>

using namespace std;




class heapSort
{
    int n;
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

    bool comp(string &a, string &b)
    {
        if (a.size() < b.size())
        {
            return 1;
        }
        else if (a.size() > b.size())
        {
            return 0;
        }
        else
        {
            return (a < b);
        }
    }

public:
    vector<string> heap;

    heapSort(int n)
    {
        this->n = n;
        heap.resize(n+1);
        for (int i = 1; i <= n; i++)
        {
            string s;
            cin >> s;
            heap[i] = s;
            int curr = i;
            while (par(curr) >= 1 && comp(heap[par(curr)], heap[curr]))
            {
                swap(heap[par(curr)], heap[curr]);
                curr = par(curr);
            }
        }
    }

    void sort()
    {
        int e = n;
        while (e > 1)
        {
            swap(heap[1], heap[e--]);
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
    }
};

int main()
{

    int n;
    cin >> n;
    heapSort hs(n);
    hs.sort();

    for (int i=1;i<=n;i++){
        cout << hs.heap[i] << " ";
    }cout << endl;

    return 0;
}