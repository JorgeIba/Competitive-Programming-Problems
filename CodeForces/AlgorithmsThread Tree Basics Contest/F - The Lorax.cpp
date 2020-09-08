#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli n, q;
vector< vector< lli > > adjList;
vector< lli > level, parent;
const lli maxN = 1e5 + 100, LOG = 22;

void prep()
{
    adjList.clear(); adjList.resize(n+1);

}


void solve()
{
    cin>>n>>q;
    prep();
}


int main () {
	//fastIO();
    lli t; cin>>t;
    while(t--) solve();

	return 0;
}