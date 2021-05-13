#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


VLL getDivs(lli n)
{
    VLL divs;
    for(lli i = 1; i*i<=n; i++)
    {
        if(n%i == 0)
        {
            divs.push_back(i);
            if(i != n/i) divs.push_back(n/i);
        }
    }
    return divs;
}

const lli INF = 1e18;
void solve()
{
    lli n; cin>>n;
    vector<lli> p(n+1), colors(n+1);
    for(int i = 1; i<=n; i++) cin>>p[i];
    for(int i = 1; i<=n; i++) cin>>colors[i];

    vector<bool> visited(n+1);
    vector< vector<lli> > cycles;
    for(int i = 1; i<=n; i++)
    {
        if(!visited[i])
        {
            int u = i;
            int sz = 0;
            VLL cycle;
            do{
                sz++;
                visited[u] = true;
                cycle.push_back(u);
                u = p[u];
            }while(u!=i);
            cycles.push_back(cycle);
        }
    }
    lli ans = INF;
    for(auto cycle: cycles)
    {
        int sz = SZ(cycle);
        auto divs = getDivs(sz);
        for(auto d: divs)
        {
            vector<bool> visited(SZ(cycle));
            for(int i = 0; i<SZ(cycle); i++)
            {
                if(!visited[i])
                {
                    int u = i;
                    int last = colors[cycle[u]];
                    bool flag = true;
                    do{
                        if(last != colors[cycle[u]]) flag = false;
                        visited[u] = true;
                        u = (u+d)%sz;
                        //cout << u << endl;
                    }while(u!=i);
                    if(flag) ans = min(ans, d);
                }
            }
        }
    }
    cout << ans << endl;
}

int main () {
	fastIO();
    lli t; cin>>t;
    while(t--) solve();

    
	return 0;
}