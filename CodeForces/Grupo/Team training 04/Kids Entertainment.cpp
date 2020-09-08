#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct Node
{
    bool topLeft=false, topRight=false, downLeft=false, downRight=false;
    lli num;
    Node(bool topLeft, bool downLeft, bool topRight,  bool downRight, lli num):
        topLeft(topLeft), topRight(topRight), downLeft(downLeft), downRight(downRight), num(num) {}
};

Node check(lli n)
{
    switch(n)
    {
        case 0:
            return Node(true, true, true, true, 6);
        case 1:
            return Node(false, false, true, true, 2);
        case 2:
            return Node(false, true, true, false, 5);
        case 3:
            return Node(false, false, true, true, 5);
        case 4:
            return Node(true, false, true, true, 4);
        case 5:
            return Node(true, false, false, true, 5);
        case 6:
            return Node(true, true, false, true, 6);
        case 7:
            return Node(false, false, true, true, 3);
        case 8:
            return Node(true, true, true, true, 7);
        case 9:
            return Node(true, false, true, true, 6);

    }
}


lli Merge (Node d1, Node d2)
{
    lli aux = d1.num + d2.num;
    if(d1.topRight == d2.topLeft && d1.downRight == d2.downLeft )
    {
        if(d1.topRight) aux--;
        if(d1.downRight) aux--;
    } 
    return aux;
}




void solve()
{
    string s; cin>>s;
    lli d1 = s[0] - '0';
    lli d2 = s[1] - '0';
    Node d11 = check(d1);
    Node d22 = check(d2);
    if(d1 == 1)
    {
        cout << (d11.num + d22.num) << endl;
    }
    else
    {
        lli res = Merge(d11, d22);
        cout << res << endl;
    }
}




int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}