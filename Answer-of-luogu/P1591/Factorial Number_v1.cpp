#include <bits/stdc++.h>
using namespace std;

int cmp(int n,int a)
{
    string nn;
    char aa = a + '0';
    nn = to_string(n);
    reverse(nn.begin(),nn.end());
    int tp = n;
    tp--;
    for(int i = 1 ; i < n; i++)
    {
        int up = 0;
        for(int j = 0; j < nn.size(); j++)
        {
            int temp = nn[j] - '0';
            int sum = temp * tp + up;
            int left = sum % 10;
            up = sum / 10;
            nn[j] = left + '0';
        }

        while(up > 0)
        {
            nn.push_back(up%10 + '0');
            up /= 10;
        }
        tp--;
    }

    int count = 0;
    for(size_t i = 0; i < nn.size(); i++)
    {
        if(nn[i] == aa) count++;
    }
    return count;
}

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> a(2, vector<int>(n));
    for(int i = 0 ; i < n; i++)
    {
        cin >> a[0][i] >> a[1][i];
    }

    vector<int> num(n);
    for(int i = 0; i < n; i++)
    {
        num[i] = cmp(a[0][i],a[1][i]);
    }

    for(int i = 0; i < n; i++)
    {
        cout << num[i] << endl;
    }

    return 0;
}