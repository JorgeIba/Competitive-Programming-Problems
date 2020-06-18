#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli n;
string s;

void add(lli idx, pair<lli,lli> &curr)
{
    switch(s[idx])
    {
        case 'R':
            curr.first++;
            break;
        case 'L':
            curr.first--;
            break;
        case 'D':
            curr.second--;
            break;
        case 'U':
            curr.second++;
            break;
    }
}


int main()
{
    fastIO();
    cin>>n;
    cin>>s;
    pair<lli,lli> curr={0,0};
    vector< pair<lli,lli> > pos(n+1);
    pos[0] = {0,0};
    for(int i = 0; i<n; i++)
    {
        add(i, curr);
        pos[i+1] = curr;
    }
    set< pair<lli,lli> > check;
    lli l = 0, r = 0, ans = 0;
    while(r<=n)
    {
        while(check.find(pos[r]) != check.end())
        {
            check.erase(pos[l++]);
        }
        ans = max(ans, r-l);
        check.insert( pos[r] );
        r++;
    }
    cout<<ans<<endl;
    return 0;
}