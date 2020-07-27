#include <bits/stdc++.h>
//Don't hack me plz :((
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

void solve()
{
    string s; cin>>s;
    cout<<s[0];
    lli index = 1;
    while(index < s.length())
    {
        cout<<s[index];
        index+=2;
    }
    cout<<endl;
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