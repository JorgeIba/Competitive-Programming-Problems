#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< vector< lli > > adjList;
vector< lli > living, happyIdx, szTree, peopleHappy, sumaHappy;

void prep(lli n)
{
    adjList.clear(); adjList.resize(n+1);
    living.clear(); living.resize(n+1);
    happyIdx.clear(); happyIdx.resize(n+1);
    szTree.clear(); szTree.resize(n+1);
    peopleHappy.clear(); peopleHappy.resize(n+1);
    sumaHappy.clear(); sumaHappy.resize(n+1);
}

bool check = true;

void dfs(lli u, lli p)
{
    szTree[u] = living[u];
    lli sumaHijos = 0;
    for(auto v: adjList[u])
    {
        if(v != p)
        {
            dfs(v, u);
            szTree[u] += szTree[v];
            sumaHijos += peopleHappy[v];
        }
    }
//    sumaHappy[u] = sumaHijos+peopleHappy[u];
    if((szTree[u] + happyIdx[u]) % 2 != 0) check = false;
    peopleHappy[u] = (szTree[u] + happyIdx[u])/2; // vatos felices al inicio que pasaron por ahi
    if(peopleHappy[u] < sumaHijos || peopleHappy[u] < 0 || peopleHappy[u] > szTree[u]) check = false;
}

void solve()
{
    lli n, k; cin>>n>>k;
    prep(n);
    for(int i = 1; i<=n; i++) cin>>living[i];
    for(int i = 1; i<=n; i++) cin>>happyIdx[i];
    for(int i = 1; i<=n-1; i++)
    {
        lli u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    check = true;
    dfs(1, -1);
    if(check)
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }

    //for(int i = 1; i<=n; i++) cout << peopleHappy[i] << " ";
}

int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--) solve();

    return 0;
}