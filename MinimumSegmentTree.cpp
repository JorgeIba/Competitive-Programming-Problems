#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

const lli INF = 100000000000LL;
using namespace std;

vector<lli> ST;
vector<lli> nums;

void build()
{
    lli n = nums.size();
    for(int i=n; i<2*n; i++)
    {
        ST[i] = nums[i-n];
    }
    for(int i=n-1; i; i--)
    {
        ST[i] = min( ST[i*2], ST[i*2 + 1] );
    }
}

lli update(lli index, lli value)
{
    lli n = nums.size();
    index += n;
    ST[index] = value;
    while(index>>1)
    {
        ST[index>>1] = min( ST[index], ST[index^1] );
        index>>=1;
    }
}

lli query(lli l, lli r)
{  
    lli n = nums.size();
    lli res = INF;
    l+=n;
    r+=n;
    while(l<=r)
    {
        if(l&1)
        {
            res = min(res,ST[l]);
            l++;
        }
        if(~r&1)
        {
            res = min(res,ST[r]);
            r--;
        }
        l>>=1;
        r>>=1;
    }
    return res;
}



int main()
{
    lli n; cin>>n;
    ST.resize(2*n, INF);
    nums.resize(n, INF);
    

    for(auto &x: nums)
    {
        cin>>x;
    }

    build();
    while(true)
    {
        lli i, v; cin>>i>>v;
        update(i,v);
        lli l,r; cin>>l>>r;
        cout<<query(l,r)<<endl;
        for(auto x: ST)
        {
            cout<<x<<" ";
        }
        cout<<endl;
    }
    

    


    return 0;
}