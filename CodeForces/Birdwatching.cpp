#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< vector< lli > > adjList;
set< lli > forbidden;
vector< set<lli> > haveSeen;

void dfs(lli u, lli p)
{
    if(haveSeen[u].size() >= 2) return;
    if(haveSeen[u].count(p)) return;
    haveSeen[u].insert(p);
    for(auto v: adjList[u])
    {
        dfs(v, p);
    }
}

int main () {
	//fastIO();
    lli n, m, t; cin>>n>>m>>t;
    adjList.resize(n+1);
    haveSeen.resize(n+1);
    for(int i = 0; i<m; i++)
    {
        lli u, v; cin>>u>>v;
        if(v == t) forbidden.insert(u);
        else
            adjList[v].push_back(u);
    }
    for(auto v: forbidden)
    {
        dfs(v, v);
    }
    vector< lli > ans;
    for(auto v: forbidden)
    {
        if(haveSeen[v].size() == 1) ans.push_back(v);
    }

    cout << (int)(ans.size()) << endl;
    sort(all(ans));
    for(auto a: ans)
    {
        cout << a << "\n";
    }

	
	return 0;
}