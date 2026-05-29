#include <bits/stdc++.h>
using namespace std;

void Multiply(vector<int>& num,int x)
{
    int carry = 0;
    for(int i = 0 ; i < num.size(); i++)
    {
        int t = num[i] * x + carry;
        num[i] = t % 10;
        carry = t / 10;
    }

    while(carry)
    {
        num.push_back(carry % 10);
        carry /= 10;
    }
}

int main()
{
    int n;
    cin >> n;

    vector<int> solution;
    int sum = 0;
    for(int i = 2; sum + i <= n; i++)
    {
        solution.push_back(i);
        sum += i;
    }

    int left = n - sum;
    for(int i = solution.size() - 1; i >= 0 && left > 0 ; i--)
    {
        solution[i]++;
        left--;
    }

    if(left)
    {
        solution[solution.size() - 1] += left;
    }

    for(int i = 0; i < solution.size() ; i++)
    {
        cout << solution[i] << " ";
    }
    cout << endl;

    vector<int> ans;
    ans.push_back(1);

    for(int i = 0; i < solution.size(); i++)
    {
        Multiply(ans,solution[i]);
    }

    for(int i = ans.size() - 1; i >= 0; i--)
    {
        cout << ans[i];
    }

    return 0;
}