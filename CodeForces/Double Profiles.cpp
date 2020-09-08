#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< vector< lli > > adj;
map<pair<lli,lli>,lli> fr;
lli n, m; 
void getHashes()
{
    lli p1 = 31, mod1 = 1e9+7, p2 = 37, mod2 = 1e8+7;
    vector< pair<lli,lli> > hashes(n+1);
    for(int i = 1; i<=n; i++)
    {
        lli hash1 = p1, magic1 = p1;
        lli hash2 = p2, magic2 = p2;
        for(auto j: adj[i])
        {
            hash1 = (hash1 + (j+97)*magic1)%mod1;
            magic1 = (magic1*p1)%mod1;
            
            hash2 = (hash2 + (j+97)*magic2)%mod2;
            magic2 = (magic2*p2)%mod2;

        }
        fr[{hash1, hash2}]++;
    }
}

int main()
{
    fastIO();
    cin>>n>>m;
    adj.resize(n+1);
    for(int i = 0; i<m; i++)
    {
        lli u, v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    //for(int i = 1; i<=n; i++) adj[i].push_back(i);
    for(int i = 1; i<=n; i++) sort(all(adj[i]));
    getHashes();
    for(int i = 1; i<=n; i++) adj[i].push_back(i);
    for(int i = 1; i<=n; i++) sort(all(adj[i]));
    getHashes();
    
    lli ans = 0;
    for(auto x: fr)
    {
        //cout << x.first << " " << x.second << endl;
        ans += ((x.second-1)*(x.second)) / 2 ;
    }
    cout << ans << endl;
    return 0;
}