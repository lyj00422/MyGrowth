#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<vector<char>> map(10,vector<char>(10));

    int C_i,C_j,F_i,F_j;
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            char s;
            cin >> s;
            if(s == 'C')
            {
                C_i = i;
                C_j = j;
            }
            if(s == 'F')
            {
                F_i = i;
                F_j = j;
            }
            map[i][j] = s;
        }
    }

    int count = 0;
    int di_dj[2][4] = {
        {-1,0,1,0},
        {0,1,0,-1}
    };
    int C_der = 0;
    int F_der = 0;
    while (C_i != F_i || C_j != F_j)
    {
        int temp_C_i = C_i + di_dj[0][C_der];
        int temp_C_j = C_j + di_dj[1][C_der];
        int temp_F_i = F_i + di_dj[0][F_der];
        int temp_F_j = F_j + di_dj[1][F_der];
        count++;
        if(temp_C_i < 0 || temp_C_i >= 10 || temp_C_j < 0 || temp_C_j >= 10 || map[C_i+di_dj[0][C_der]][C_j+di_dj[1][C_der]] == '*')
        {
            C_der = (C_der+1) % 4;
        }
        else
        {
            C_i = temp_C_i;
            C_j = temp_C_j;
        }

        if(temp_F_i < 0 || temp_F_i >= 10 || temp_F_j < 0 || temp_F_j >= 10 || map[F_i+di_dj[0][F_der]][F_j+di_dj[1][F_der]] == '*')
        {
            F_der = (F_der+1) % 4;
        }
        else
        {
            F_i = temp_F_i;
            F_j = temp_F_j;
        }
    }

    if (count > 160000)
    {
        cout << 0 << endl;
        return 0;
    }
    cout << count << endl;
}