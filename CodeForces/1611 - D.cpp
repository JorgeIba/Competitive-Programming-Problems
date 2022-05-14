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

vector< vector<lli> > adjList;
set<lli> poss;
vector<lli> p;

bool check(lli idx)
{
    if(idx == SZ(p)) return true;

    lli u = p[idx];
    if( !poss.count(u) ) return false;
    poss.erase(u);


    for(auto v: adjList[u])
    {
        poss.insert(v);
    }


    return check(idx+1);
}




void solve()
{
    lli n; cin>>n;
    vector<lli> b(n);
    p.resize(n);
    for(auto &x: b) cin>>x;
    for(auto &x: p) cin>>x;

    for(auto &x: b) x--;
    for(auto &x: p) x--;

    adjList.clear();
    poss.clear();
    adjList.resize(n);
    for(int i = 0; i<n; i++)
    {
        if(b[i] == i) continue;
        adjList[b[i]].push_back(i);
    }



    lli root = -1;
    for(int i = 0; i<n; i++)
    {
        if(b[i] == i) root = i;
    }


    
    poss.insert(root);
    if(!check(0))
    {
        cout << -1 << endl;
        return;
    }



    vector<lli> dist(n);
    for(int i = 0; i<n; i++)
    {
        dist[ p[i]  ] = i;
    }


    queue<lli> q;

    q.push(root);

    vector<lli> ans(n);
    while(!q.empty())
    {
        lli u = q.front(); q.pop();

        for(auto v: adjList[u])
        {
            ans[v] = dist[v] - dist[u];
            q.push(v);
        }
    }

    for(auto x: ans) cout << x << " ";
    cout << endl;


    
    
}



int main () {
	fastIO();
    lli t; cin>>t;

    while(t--) solve();
	


	return 0;
}

