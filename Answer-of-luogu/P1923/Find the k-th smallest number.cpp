#include <bits/stdc++.h>
using namespace std;

int quick_select(vector<int>& a, int l, int r, int k, mt19937& rng)
{
    while (l <= r)
    {
        int pivot = a[l + rng() % (r - l + 1)];

        int lt = l;
        int i = l;
        int gt = r;

        while (i <= gt)
        {
            if (a[i] < pivot)
            {
                swap(a[lt], a[i]);
                lt++;
                i++;
            }
            else if (a[i] > pivot)
            {
                swap(a[i], a[gt]);
                gt--;
            } else i++;
        }

        if (k < lt) r = lt - 1;
        else if (k > gt) r = gt + 1;
        else return pivot;
    }

    return -1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n,k;
    cin >> n >> k;

    vector<int> a(n);

    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cout << quick_select(a,0,n-1,k,rng);
}