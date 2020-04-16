#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;


vector<lli> ST;
lli n;

void build(vector<lli> nums)
{
    for(lli i = n; i<2*n; i++)
    {
        ST[i] = nums[i-n];
    }
    for(lli i = n-1; i; i--)
    {
        ST[i] = ST[i<<1] + ST[i<<1|1];
    }
}

void update(lli index, lli value)
{
    index += n;
    ST[index] = value;

    while(index>>1)
    {
        ST[index>>1] = ST[index] + ST[index^1];
        index >>=1;
    }
}

lli query(lli l, lli r)
{
    l+=n;
    r+=n;
    lli ans = 0;
    while(l<=r)
    {
        if(l&1)
        {
            ans = ans+ST[l];
            l++;
        }
        if(!(r&1))
        {
            ans = ans+ST[r];
            r--;
        }
        l/=2;
        r/=2;
        //cout<<l<<" "<<r<<endl;
    }
    return ans;
}


int main()
{
    cin>>n;
    lli neutro = 0;
    ST.resize(2*n, neutro);
    vector<lli> nums(n);
    for(auto &x: nums)
    {
        cin>>x;
    }
    build(nums);

    while(true)
    {
        lli i, v; cin>>i>>v;
        update(i,v);
        for(auto x: ST)
        {
            cout<<x<<" ";
        }
        cout<<endl;
        lli j,k; cin>>j>>k;
        cout<<query(j,k)<<endl;
    }

    return 0;
}