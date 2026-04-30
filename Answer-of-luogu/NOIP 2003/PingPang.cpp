#include <iostream>
#include <string>
#include <cmath>
using namespace std;

void solve(const string& s,int limit);

int main()
{
    string record;
    char ch;
    while(cin >> ch && ch != 'E')
    {
        record.push_back(ch);
    }
    solve(record,11);
    cout << endl;
    solve(record,21);
    return 0;
}

void solve(const string& s,int limit)
{
    int a = 0,b = 0;
    for(char ch : s)
    {
        if(ch == 'W') a++;
        else b++;
        if((a >= limit || b >= limit) && abs(a - b) >= 2)
        {
            cout << a << ":" << b << endl;
            a = b = 0;
        }
    }
    cout << a << ":" << b << endl;
}