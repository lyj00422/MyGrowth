#include <bits/stdc++.h>
using namespace std;

void merge(vector<int>& num,int l,int mid,int r)
{
    vector<int> temp(r - l+ 1);
    int i = l,j = mid + 1,k = 0;
    while(i <= mid && j <= r)
    {
        if(num[i] <= num[j]) temp[k++] = num[i++];
        else temp[k++] = num[j++];
    }
    while(i <= mid) temp[k++] = num[i++];
    while(j <= r) temp[k++] = num[j++];

    for(int p = 0; p < k; p++)
    {
        num[l+p] = temp[p];
    }
}

void my_sort(vector<int>& num,int l,int r)
{
    if(l >= r) return;
    int mid = (l+r) >> 1;
    my_sort(num,l,mid);
    my_sort(num,mid+1,r);
    merge(num,l,mid,r);
}

int main()
{
    int n;
    cin >> n;
    vector<int> num(n);
    for(int i = 0; i < n; i++)
    {
        cin >> num[i];
    }

    my_sort(num,0,n-1);

    for(int i = 0; i < n; i++)
    {
        cout << num[i] << " ";
    }
    return 0;
}