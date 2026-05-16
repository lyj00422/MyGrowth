#include <bits/stdc++.h>
using namespace std;

int main()
{
    int num,A,B;
    cin >> num >> A >> B;

    vector<int> Ain;
    vector<int> Bin;

    int score[5][5] = 
    {
        {0,0,1,1,0},
        {1,0,0,1,0},
        {0,1,0,0,1},
        {0,0,1,0,1},
        {1,1,0,0,0},
    };

    for(int i = 0; i < A ; i++)
    {
        int s;
        cin >> s;
        Ain.push_back(s);
    }

    for(int i = 0; i < B; i++)
    {
        int s;
        cin >> s;
        Bin.push_back(s);
    }

    int A_goal = 0;
    int B_goal = 0;

    for(int i = 0; i < num; i++)
    {
        int a_i = i % A;
        int b_i = i % B;
        int a_out = Ain[a_i];
        int b_out = Bin[b_i];
        if(score[a_out][b_out] == 1)
        {
        A_goal++;
        }
        else if(score[b_out][a_out] == 1)
        {
            B_goal++;
        }
    }

    cout << A_goal << " " << B_goal << endl;
    return 0;
}