#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< lli > ST, lazy;

//10
void propagate(lli id, lli l, lli r, lli value)
{
    ST[id] += (r-l+1)*value; //Suma
    if(l!=r)
    {
        lazy[2*id] += value;
        lazy[2*id + 1] += value;
    }
}
//16
void update(lli id, lli l, lli r, lli start, lli end, lli value)
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
        ST[id] = ST[2*id] + ST[2*id + 1];
    }
}
//14
lli query(lli id, lli l, lli r, lli start, lli end) 
{
    if(lazy[id] != 0){
        propagate(id, l, r, lazy[id]);
        lazy[id] = 0;
    }
    if( end < l || r < start) return 0;
    if ( start <= l && r <= end  ) return ST[id];
    else{
        lli mid = l + (r-l)/2;
        return query(2*id, l, mid, start, end) + query(2*id+1, mid+1, r, start, end);
    }
}

struct Query
{
    lli d, value;
    Query(): d(0), value(0) {}
    Query(lli d, lli value): d(d), value(value) {}
};


vector< vector<lli> > adjList;
vector< vector< Query* > > queries;
vector< lli > ans;
lli n; 

void prep(lli n)
{
    adjList.resize(n+1);
    ST.resize(4*(n+1) + 10); // ST sobre profundidad
    lazy.resize(4*(n+1) + 10);
    queries.resize(n+1);
    ans.resize(n+1);
}


void dfs(lli u, lli p, lli depth)
{
    for(Query *Q: queries[u])
    {
        lli l = depth, r = depth + Q->d, value = Q->value;
        //if(u == 1) cout << l << " " << r << endl;
        update(1, 1, n, l, r, value); // Agregando a todos los nodos de profundidad l a r
    }

    ans[u] += query(1, 1, n, depth, depth);


    for(auto v: adjList[u])
    {
        if(v != p)
        {
            dfs(v, u, depth+1);
        }
    }

    for(Query *Q: queries[u])
    {
        lli l = depth, r = depth + Q->d, value = Q->value;
        update(1, 1, n, l, r, -value); //quitas lo agregado
    }
}



int main()
{
    fastIO();
    cin>>n;
    prep(n);
    for(int i = 0; i < n-1; i++)
    {
        lli u, v; cin>> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    lli q; cin>>q;
    while(q--)
    {
        lli v, d, x; cin>>v>>d>>x;
        Query *N = new Query(d, x);
        queries[v].push_back(N);
    }

    dfs(1, -1, 1);

    for(int i = 1; i<=n; i++)
    {
        cout << ans[i] << " ";
    }
    
    
    return 0;
}