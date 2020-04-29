#include <bits/stdc++.h>
#define lli long long int 
using namespace std;


vector<lli> ST;
vector<lli> lazy;

void propagate(lli id, lli l, lli r, lli value)
{
    ST[id] += (r-l+1)*value;
    if(l!=r)
    {
        lazy[2*id] += value;
        lazy[2*id + 1] += value;
    }
}

void update(lli id, lli l, lli r, lli start, lli end, lli value) // l y r en donde estas, start y end donde quieres
{
 //   cout<<id<<" "<<l<<" "<<r<<endl;
    if(lazy[id] != 0)
    {
        propagate(id, l, r, lazy[id]);
        lazy[id] = 0;
    }
    if( end < l || r < start)
    {
        return;
    }
    if ( start <= l && r <= end  )
    {
        propagate(id, l, r, value);
    } 
    else
    {
        lli mid = (l+r)/2;
        update(2*id, l, mid, start, end, value);
        update(2*id+1, mid+1, r, start, end, value);
        ST[id] = ST[2*id] + ST[2*id + 1];
    }
}


lli query(lli id, lli l, lli r, lli start, lli end) 
{
    if(lazy[id] != 0)
    {
        propagate(id, l, r, lazy[id]);
        lazy[id] = 0;
    }
    if( end < l || r < start) return 0;
    if ( start <= l && r <= end  ) return ST[id];
    else
    {
        lli mid = l + (r-l)/2;
        return query(2*id, l, mid, start, end) + query(2*id+1, mid+1, r, start, end);
    }
}




int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli t; cin>>t;
    while(t--)
    {
        lli n, c; cin>>n>>c;
        ST.resize(4*n + 5, 0);
        lazy.resize(4*n + 5, 0);
        while(c--)
        {
            lli type; cin>>type;
            if(type==0)
            {
                lli l, r, v; cin>>l>>r>>v;
                update(1, 1, n, l, r, v);
            }
            else
            {
                lli l, r; cin>>l>>r;
                cout<<query(1, 1, n, l, r)<<endl;
            }
        }
        ST.clear();
        lazy.clear();
    }
    return 0;
}