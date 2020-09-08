#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli maxN = 4*(1e5) + 100, maxC = 65;;
vector< lli > adjList[maxN];
vector< bitset<maxC> > ST;
vector< bitset<maxC> > lazy;
lli colors[maxN], reach[maxN][2], work[maxN];
lli n, m, cnt = 1;

//10
void propagate(lli id, lli l, lli r, bitset<maxC> value)
{
    ST[id] = value; //Suma
    if(l!=r)
    {
        lazy[2*id] = value;
        lazy[2*id + 1] = value;
    }
}
//16
void update(lli id, lli l, lli r, lli start, lli end, bitset<maxC> value)
{
    if(lazy[id] != 0){
        propagate(id, l, r, lazy[id]);
        lazy[id] = 0;
    }
    if( end < l || r < start) return;
    if ( start <= l && r <= end) propagate(id, l, r, value);
    else{
        lli mid = (l+r)/2;
        update(2*id, l, mid, start, end, value);
        update(2*id+1, mid+1, r, start, end, value);
        ST[id] = (ST[2*id] | ST[2*id + 1]);
    }
}
//14
bitset<maxC> query(lli id, lli l, lli r, lli start, lli end) 
{
    if(lazy[id] != 0){
        propagate(id, l, r, lazy[id]);
        lazy[id] = 0;
    }
    if( end < l || r < start) return 0;
    if ( start <= l && r <= end  ) return ST[id];
    else{
        lli mid = l + (r-l)/2;
        return ((query(2*id, l, mid, start, end) | query(2*id+1, mid+1, r, start, end)));
    }
}



void dfs(lli u, lli p)
{
    reach[u][0] = cnt;
    work[cnt++] = u;
    for(auto v: adjList[u])
    {
        if(v!=p)
        {
            dfs(v, u);
        }
    }
    reach[u][1] = cnt-1;
}


int main () {
	fastIO();
    cin>>n>>m;
    ST.resize(4*(n+1));
    lazy.resize(4*(n+1));

    for(int i = 1; i<=n; i++) cin>>colors[i];
    for(int i = 0; i<n-1; i++)
    {
        lli u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    dfs(1, -1);

    for(int i = 1; i<=n; i++)
    {
        bitset<maxC> aux;
        aux[colors[work[i]]] = 1;
        update(1, 1, n, i, i, aux);
    }
    while(m--)
    {
        lli t; cin>>t;
        if(t == 1)
        {
            lli v, c; cin>>v>>c;
            bitset<maxC> aux = 0;
            aux[c] = 1;
            update(1, 1, n, reach[v][0], reach[v][1], aux);
        }
        else
        {
            lli v; cin>>v;
            //cerr << reach[v][0] << " " << reach[v][1] << endl;
            cout << query(1, 1, n, reach[v][0], reach[v][1]).count() << endl;
        }
    }

	return 0;
}