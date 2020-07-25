#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<lli> nums, blocks;
lli n, S;

void build()
{
    for(int i = 0; i<n; i++) blocks[i/S] += nums[i];
}


void update(lli value, lli idx)
{
    lli k = idx / S, res = 0;
    nums[idx] = value;
    for(int i = k*S, end = min(n, (k+1)*S ) - 1; i<=end; i++) res+= nums[i];
    blocks[k] = res;
}



lli query(lli l, lli r)
{
    lli L = l/S, R = r/S, res = 0;
    if(L==R)
    {
        for(int i = l; i <= r; i++)
        {
            res += nums[i];
        }
    }
    else
    {
        for(int i = l, end = (L+1)*S - 1; i<=end; i++) res += nums[i];
        for(int i = L + 1; i<=R-1; i++) res += blocks[i];
        for(int i = R*S; i<=r ; i++) res += nums[i];
    }
    return res;
}


int main()
{
    //fastIO();
    cin>>n;
    S = sqrt(n + .0) + 1;
    nums.resize(n); blocks.resize(S);
    for(auto &x: nums)
        cin>>x;

    build();

    while(true)
    {
        lli l, r; cin>>l>>r;
        cout<<query(l,r)<<endl;
        lli value, idx; cin>>idx>>value;
        update(value, idx);
    }

    return 0;
}