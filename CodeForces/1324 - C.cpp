#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void solve()
{
    string s; cin>>s;
    lli d = 1, aux = 1;
    for(int i = 0; i<s.length(); i++)
    {
        char c = s[i];
        if( c == 'L' )
        {
            aux++;
        }
        else
        {
            d = max(d, aux);
            aux = 1;
        }
    }
    d = max(d,aux);
    cout<<d<<endl;


}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}