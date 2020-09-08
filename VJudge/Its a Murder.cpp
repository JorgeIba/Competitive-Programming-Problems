#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
using namespace std;

const lli MAX = 1000010;

lli n;
vector<lli> ST;


void update(lli index, lli value)
{
    ST[index += MAX] += value;
    while(index>>1)
    {
        ST[index>>1] = ST[index] + ST[index^1];
        index >>= 1;
    }
}

lli query(lli r)
{
    lli res = 0;
    lli l = MAX;

    for( r+=MAX; l<=r; l>>=1, r>>=1)
    {
        //cout<<l<<" "<<r<<endl;
        if(l&1)
        {
            res += ST[l++];
        }
        if(!(r&1))
        {
            res += ST[r--];
        }
    }
    //cout<<"!#!@# "<<res<<endl;
    return res;
}


void solve()
{
    cin>>n;
    ST.clear();
    ST.resize(2*MAX, 0);
    lli res = 0;
    for(lli i = 0; i<n; i++)
    {
        lli x; cin>>x;
        if(x==0) continue;
        update(x, x);
        res += query(x-1);
        //cout<<query(x-1)<<" ";
    }
    cout<<res<<endl;
}


int main()
{
    
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}


