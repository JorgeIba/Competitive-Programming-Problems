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
    lli n; cin>>n;
    vector<lli> nums(n);
    lli even = 0, odd = 0;
    for(int i = 0; i<n; i++)
    {
        lli x; cin>>x;
        if( i&1  && ~x&1  ) even++;
        else if (~i&1 && x&1) odd++;
    }
    if(odd != even)
    {
        cout<<-1<<endl;
    }
    else
    {
        cout<< even << endl;
    }



}


int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--) solve();
    return 0;
}