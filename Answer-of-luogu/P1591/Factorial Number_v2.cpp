#include <bits/stdc++.h>
using namespace std;

int CountDigitInFactorial(int n,int a)
{
    vector<int> num;
    num.push_back(1);

    for(int i = 2; i <= n; i++)
    {
        int carry = 0;

        for(int j = 0; j < num.size(); j++)
        {
            int sum = num[j]*i + carry;
            num[j] = sum % 10;
            carry = sum / 10;
        }

        while(carry > 0)
        {
            num.push_back(carry % 10);
            carry /= 10;
        }
    }

    int ans = 0;
    for(int i = 0; i < num.size(); i++)
    {
        if(num[i] == a) ans++;
    }

    return ans;
}

int main()
{
    int T;
    cin >> T;

    while(T--)
    {
        int n,a;
        cin >> n >> a;

        cout << CountDigitInFactorial(n,a) << endl;
    }
    return 0;
}