#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< lli > ST, lazy;
const lli INF = 1e18;

//10
void propagate(lli id, lli l, lli r, lli value)
{
    ST[id] = value;
    if(l!=r)
    {
        lazy[2*id] = value;
        lazy[2*id + 1] = value;
    }
}
//16
void update(lli id, lli l, lli r, lli start, lli end, lli value)
{
    if(lazy[id] != INF){
        propagate(id, l, r, lazy[id]);
        lazy[id] = INF;
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
    if(lazy[id] != INF){
        propagate(id, l, r, lazy[id]);
        lazy[id] = INF;
    }
    if( end < l || r < start) return 0;
    if ( start <= l && r <= end  ) return ST[id];
    else{
        lli mid = l + (r-l)/2;
        return query(2*id, l, mid, start, end) + query(2*id+1, mid+1, r, start, end);
    }
}



int main()
{
    fastIO();
    lli n, q; cin>>n>>q;
    vector< lli > a(n);
    vector< lli > b(n);
    ST.resize(4*(n+1), INF), lazy.resize(4*(n+1), INF);
    for(auto &x: a) cin>>x;
    for(auto &x: b) cin>>x;

    
    while(q--)
    {
        lli t; cin>>t;
        if(t == 1)  
        {
            lli x, y, k; cin>>x>>y>>k;
            lli diff = x-y;
            update(1, 1, n, y, y+k-1, diff); // de y a y+k, con el diff
        }
        else
        {
            lli x; cin>>x;
            lli diff = query(1, 1, n, x, x);
            //cout<< diff << endl;
            if(diff != INF) //checar si el diff existe o nel
            {
                assert((x + diff - 1) >= 0);
                cout << a[ x + diff - 1 ] << endl;
            }
            else
            {
                cout << b[x-1] << endl;
            }            
        }
    }

    return 0;
}