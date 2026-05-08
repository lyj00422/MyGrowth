#include <bits/stdc++.h>
using namespace std;

int main() 
{
    string a,b;
    cin >> a >> b;

    if(a == "0" || b == "0")
    {
        cout << 0;
        return 0;
    }

    int n = a.size();
    int m = b.size();

    vector<int> ans(n+m,0);

    for(int i = n-1 ; i >=0 ; i--)
    {
        for(int j = m-1; j >= 0; j--)
        {
            int x = a[i] - '0';
            int y = b[j] - '0';

            int sum = x*y + ans[i+j+1];

            ans[i+j+1] = sum % 10;
            ans[i+j] += sum/10;
        }
    }

    int pos = 0;
    while(pos+1 < ans.size() && ans[pos] == 0)
    {
        pos++;
    }

    for(int k = pos; k < ans.size() ; k++)
    {
        cout << ans[k];
    }
    return 0;
}