#include <bits/stdc++.h>
using namespace std;
class person
{
    public:
    int dir;
    string job;
    person(int n,string a) : dir(n),job(a){};
};

typedef struct Node
{
    Node* prev;
    Node* next;
    person humman;
    Node(int n,string a) : prev(nullptr), next(nullptr), humman(person(n,a)) {};
}Node;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin >> n >> m;
    Node* head;
    Node* tail;
    for(int i = 0; i < n; i++)
    {
        int num;
        string str;
        cin >> num >> str;
        if(i == 0)
        {
            head = new Node(num,str);
            tail = head;
        }
        else if(i == n-1)
        {
            Node* node = new Node(num,str);
            node->next = head;
            node->prev = tail;
            tail->next = node;
            head->prev = node;
        }
        else
        {
            Node* node = new Node(num,str);
            node->prev = tail;
            tail->next = node;
            tail = node;
        }
    }
    Node* now = head;
    for(int i = 0; i < m; i++)
    {
        int dir1;
        int num;
        cin >> dir1 >> num;
        if(!dir1)
        {
            if(!now->humman.dir)
            {
                for(int i = 0; i < num ; i++)
                {
                    now = now->prev;
                }
            }
            else
            {
                for(int i = 0; i < num; i++)
                {
                    now = now->next;
                }
            }
        }
        else
        {
            if(!now->humman.dir)
            {
                for(int i = 0; i < num; i++)
                {
                    now = now->next;
                }
            }
            else
            {
                for(int i = 0; i < num; i++)
                {
                    now = now->prev;
                }
            }
        }
    }
    cout << now->humman.job << endl;
}