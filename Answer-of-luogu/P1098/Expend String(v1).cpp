#include <bits/stdc++.h>
using namespace std;

int main()
{
    int p1,p2,p3;
    cin >> p1 >> p2 >> p3;
    string s;
    cin >> s;

    for(int i = 0; i < (int)s.size() ; i++)
    {
        if(i == 0 || i == (int)s.size() - 1)
        {
            cout << s[i];
            continue;
        }

        if(s[i] == '-')
        {
            if(islower(s[i-1]) && islower(s[i+1]))
            {
                int gap = s[i+1] - s[i-1];
                if(gap <= 0)
                {
                    cout << s[i];
                    continue;
                }

                if(gap == 1) continue;

                char output;
                int sign;
                switch(p1)
                {
                    case 1:
                    switch(p3)
                    {
                        case 1:
                        output = s[i-1] + 1;
                        sign = 1;
                        break;

                        case 2:
                        output = s[i+1] - 1;
                        sign = -1;
                        break;
                    }
                    break;

                    case 2:
                    switch(p3)
                    {
                        case 1:
                        output = toupper(s[i-1] + 1);
                        sign = 1;
                        break;

                        case 2:
                        output = toupper(s[i+1] - 1) ;
                        sign = -1;
                        break;
                    }
                    break;

                    case 3:
                    output = '*';
                    break;
                }

                int num = gap -1;
                for(int j = 0 ; j < num; j++)
                {
                    if(output == '*')
                    {
                        for(int k = 0; k < p2; k++)
                        {
                            cout << output;
                        }
                        continue;
                    }

                    for(int k = 0; k < p2; k++)
                    {
                        cout << output;
                    }
                    if(sign > 0) output++;
                    else output--;
                }
            }
            else if(isdigit(s[i-1]) && isdigit(s[i+1]))
            {
                int gap = s[i+1] - s[i-1];
                if(gap <= 0)
                {
                    cout << s[i];
                    continue;
                }
                if(gap == 1)
                {
                    continue;
                }

                char output;
                int sign;
                switch(p1)
                {
                    case 3:
                    output = '*';
                    break;

                    default:
                    switch(p3)
                    {
                        case 1:
                        output = s[i-1] + 1;
                        sign = 1;
                        break;

                        case 2:
                        output = s[i+1] - 1;
                        sign = -1;
                        break;
                    }
                    break;
                }

                int num = gap - 1;
                for(int j = 0; j < num; j++)
                {
                    if(output == '*')
                    {
                    for(int k = 0; k < p2; k++)
                    {
                        cout << output;
                    }
                        continue;
                    }

                    for(int k = 0; k < p2; k++)
                    {
                        cout << output;
                    }
                    if(sign > 0) output++;
                    else output--;
                }
            }
            else
            {
                cout << s[i];
            }
        }
        else
        {
            cout << s[i];
        }
    }
}