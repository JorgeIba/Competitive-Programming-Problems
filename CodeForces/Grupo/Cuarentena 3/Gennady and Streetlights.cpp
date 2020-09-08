#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< vector<lli> > adj;
vector< pair<lli,lli> > aplanado;
vector<lli> nums, ST, lazy;
lli fin = 1;

void aplanation(lli u, lli p)
{
    aplanado[u].first = fin++;
    for(auto v: adj[u])
        if(v!=p)
            aplanation(v, u);
    
    aplanado[u].second = fin-1;
    return ;
}


void build(lli id, lli l, lli r)
{
    if(l==r)
    {
        ST[id] = nums[l]; return;
    }
    lli mid = l + (r-l)/2;
    build(2*id, l, mid);
    build(2*id + 1, mid+1, r);
    ST[id] = ST[2*id] + ST[2*id+1];
}


//10
void propagate(lli id, lli l, lli r)
{
    ST[id] = (r-l+1) - ST[id]; //Suma
    lazy[id] = false;
    if(l!=r)
    {
        lazy[2*id] = !lazy[2*id];
        lazy[2*id + 1] = !lazy[2*id+1];
    }
}

//16
void update(lli id, lli l, lli r, lli start, lli end)
{
    if(lazy[id]){
        propagate(id, l, r);
    }
    if( end < l || r < start) return;
    if ( start <= l && r <= end) propagate(id, l, r);
    else{
        lli mid = (l+r)/2;
        update(2*id, l, mid, start, end);
        update(2*id+1, mid+1, r, start, end);
        ST[id] = ST[2*id] + ST[2*id + 1];
    }
}

//14
lli query(lli id, lli l, lli r, lli start, lli end) 
{
    if(lazy[id]){
        propagate(id, l, r);
    }
    if( end < l || r < start) return 0;
    if ( start <= l && r <= end  ) return ST[id];
    else{
        lli mid = l + (r-l)/2;
        return query(2*id, l, mid, start, end) + query(2*id+1, mid+1, r, start, end);
    }
}

void initialize(lli n)
{
    adj.resize(n+1);
    aplanado.resize(n+1), nums.resize(n+1);
    ST.resize(4*n+10); lazy.resize(4*n+10);
}

int main()
{
    fastIO();
    lli n; cin>>n;
    vector< lli > states(n+1);
    initialize(n);
    forn(i,1,n+1)
        cin>>states[i];

    forn(i,0,n-1)
    {
        lli u, v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    aplanation(1, -1);

    for(int i = 1; i<=n; i++)
        nums[ aplanado[i].first ] = states[i];


    build(1, 1, n);
    lli q; cin>>q;
    while(q--)
    {
        lli t, x; cin>>t>>x;
        lli l= aplanado[x].first, r = aplanado[x].second;
        if(t==1)
            update(1,1,n,l,r);
        else
            cout<< (r-l+1) - query(1, 1, n, l, r)<<endl;   
    }
    
    
    return 0;
}