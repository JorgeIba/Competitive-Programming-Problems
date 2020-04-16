#include <bits/stdc++.h>
#define lli long long int

using namespace std;

const lli MAX = 1000010;
vector<lli> ST;

void update(lli index, lli value)
{
    ST[index+=MAX] += value;
    while(index>>1)
    {
        ST[index>>1] = ST[index] + ST[index^1];
        index >>=1;
    }
}

lli query(lli index)
{
    lli res = 0;
    for(lli l = MAX, r = index+MAX; l<=r; l>>=1, r>>=1)
    {
        if(l&1)
        {
            res += ST[l++];
        }
        if(~r&1)
        {
            res += ST[r--];
        }
    }
    return res;
}



void solve()
{
    lli n; cin>>n;
    lli res = 0;
    ST.clear();
    ST.resize(2*MAX, 0);
    while(n--)
    {
        lli x; cin>>x;
        res += query(x-1);
        update(x,x);
    }
    cout<<res<<endl;
}


int main()
{
    lli t; cin>>t;
    while(t--) solve();
    return 0;
}