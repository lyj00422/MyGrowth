#include <bits/stdc++.h>
using namespace std;

const int LEN = 500;

// 高精度乘法，只保留最后 500 位
vector<int> multiply(vector<int> a, vector<int> b)
{
    vector<int> c(LEN, 0);

    for(int i = 0; i < LEN; i++)
    {
        for(int j = 0; j < LEN && i + j < LEN; j++)
        {
            c[i + j] += a[i] * b[j];
        }
    }

    for(int i = 0; i < LEN - 1; i++)
    {
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    }

    c[LEN - 1] %= 10;

    return c;
}

// 快速幂，计算 2^p 的最后 500 位
vector<int> quick_pow(int p)
{
    vector<int> ans(LEN, 0);
    vector<int> base(LEN, 0);

    ans[0] = 1;
    base[0] = 2;

    while(p > 0)
    {
        if(p & 1)
        {
            ans = multiply(ans, base);
        }

        base = multiply(base, base);
        p >>= 1;
    }

    return ans;
}

int main()
{
    int p;
    cin >> p;

    int digits = floor(p * log10(2)) + 1;
    cout << digits << endl;

    vector<int> num = quick_pow(p);

    // 2^p - 1
    num[0]--;

    for(int i = 0; i < LEN; i++)
    {
        if(num[i] < 0)
        {
            num[i] += 10;
            num[i + 1]--;
        }
    }

    // 倒序输出最后 500 位
    for(int i = LEN - 1; i >= 0; i--)
    {
        cout << num[i];

        if((LEN - i) % 50 == 0)
        {
            cout << '\n';
        }
    }

    return 0;
}