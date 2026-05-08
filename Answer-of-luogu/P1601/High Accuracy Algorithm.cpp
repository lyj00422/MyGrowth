#include <bits/stdc++.h>
using namespace std;

int main() {
    string a,b;
    cin >> a >> b;

    int i = a.size() - 1;
    int j = b.size() - 1;
    int carry = 0; //进位
    string ans;

    while(i >= 0 || j >= 0 || carry)
    {
        int x = 0;
        int y = 0;

        if(i >= 0)
        {
            x = a[i] - '0';
            i--;
        }

        if(j >= 0)
        {
            y = b[j] - '0';
            j--;
        }

        int sum = x + y + carry;

        ans.push_back(sum % 10 + '0');
        carry = sum / 10;
    }

    reverse(ans.begin(),ans.end()); //反转结果，本来是倒着来的
    int pos = 0;
    while(pos + 1 < ans.size() && ans[pos] == 0)//最后一位不能删除，比如结果就是0
    {
        pos++;
    } //删除前导零
    cout << ans.substr(pos);

    return 0;
}