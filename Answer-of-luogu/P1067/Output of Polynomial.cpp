#include <bits/stdc++.h>
using namespace std;

int main()
{
    int num;
    cin >> num;
    vector<int> nums(num+1);
    for(int i = 0; i <= num; i++)
    {
        cin >> nums[i];
    }

    bool first = true;

    for(int i = 0 ; i <= num; i++)
    {
        int coef = nums[i];
        int exp = num-i;
        if(coef == 0) continue;

        if(first)
        {
            if(coef < 0) cout << "-";
        }
        else
        {
            if(coef>0) cout << "+";
            else cout << "-";
        }

        int abscoef = abs(coef);

        if(exp == 0)
        {
            cout << abscoef;
        }
        else
        {
            if(abscoef != 1)
            {
                cout << abscoef;
            }

            if(exp == 1)
            {
                cout << "x";
            }
            else
            {
                cout << "x^" << exp;
            }
        }
        first = false;
    }
    return 0;
}