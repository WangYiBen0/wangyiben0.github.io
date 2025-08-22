#include <bits/stdc++.h>
using namespace std;
string a;
map<string, string> m;
queue<string> q;
void A(string x)
{
    string xx = x;
    for (int i = 0; i < 4; i++)
    {
        char x1 = x[i];
        x[i] = x[7 - i];
        x[7 - i] = x1;
    }
    if (m.count(x) == 0)
    {
        q.push(x);
        m[x] = m[xx] + 'A';
    }
    return;
}
void B(string x)
{
    string xx = x;
    x[0] = xx[3], x[1] = xx[0], x[2] = xx[1], x[3] = xx[2], x[4] = xx[5], x[5] = xx[6], x[6] = xx[7], x[7] = xx[4];
    if (m.count(x) == 0)
    {
        q.push(x);
        m[x] = m[xx] + 'B';
    }
    return;
}
void C(string x)
{
    string xx = x;
    x[1] = xx[6], x[2] = xx[1], x[5] = xx[2], x[6] = xx[5];
    if (m.count(x) == 0)
    {
        q.push(x);
        m[x] = m[xx] + 'C';
    }
    return;
}
void bfs()
{
    q.push("12345678");
    m["12345678"] = "";
    while (q.empty() == false)
    {
        A(q.front());
        B(q.front());
        C(q.front());
        if (m.count(a) != 0)
        {
            cout << m[a].size() << endl
                 << m[a];
            return;
        }
        q.pop();
    }
    return;
}
int main()
{
    for (int i = 0; i < 8; i++)
    {
        char a1;
        cin >> a1;
        a += a1;
        getchar();
    }
    bfs();
    return 0;
}
