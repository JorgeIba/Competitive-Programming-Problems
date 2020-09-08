#include <bits/stdc++.h>
#define lli long long int

using namespace std;

lli dp[105][100010];
lli n, k;
vector< pair<lli,lli> > items;

lli funcion(lli index, lli sum)
{
    if((index == items.size())and(sum<=k))
    {
        return 0;
    }
    if((index == items.size())and(sum>k))
    {
        return -10000000000LL;
    }
    if(sum > k)
    {
        return -100000000000LL;
    }
    if(sum == k)
    {
        return 0;
    }
    if(dp[index][sum] != -1)
    {
        return dp[index][sum];
    }
    lli si = funcion(index+1, sum+items[index].first) + items[index].second;
    lli no = funcion(index+1, sum);

    return dp[index][sum] = max(si,no);
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    memset(dp, -1, sizeof(dp));
    cin>>n>>k;
    items.resize(n);
    for(auto &x: items)
    {
        cin>>x.first>>x.second;
    }
    cout<<funcion(0,0)<<endl;

    return 0;
}