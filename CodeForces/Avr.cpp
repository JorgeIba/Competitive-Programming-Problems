#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

vector< pair<lli,lli> > neg;


int dp[120][350000];

bool compare(pair<lli,lli> a, pair<lli,lli> b)
{
    return (a.first + a.second) >= (b.first + b.second);
}


lli funcion(lli i, lli rating)
{
    if(i == neg.size())
    {
        return 0;
    }

    if(dp[i][rating] != -1)
    {
        return dp[i][rating];
    }

    pair<lli,lli> curr = neg[i];
    if((rating >= curr.first)and(rating + curr.second >= 0))
    {
        lli no = funcion(i+1, rating);
        lli si = funcion(i+1, rating + curr.second) + 1;
        return dp[i][rating] = max(si,no);

    }
    else
    {
        return dp[i][rating] = funcion(i+1, rating);
    }

}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n, r; cin>>n>>r;
    vector< pair<lli,lli> > pos;
    memset(dp, -1, sizeof(dp));
    for(int i=0; i<n; i++)
    {
        lli x1, x2; cin>>x1>>x2;
        if(x2>=0)
        {
            pos.push_back({x1,x2});
        }
        else
        {
            neg.push_back({x1, x2});
        }    
    }

    sort(pos.begin(), pos.end());
    sort(neg.begin(), neg.end(), compare);

    lli res = 0;

    for(auto x: pos)
    {
        if(r >= x.first)
        {
            r += x.second;
            res++;
        }
    }

    
    res += funcion(0, r);

    if(res == n)
    {
        cout<<"YES\n";
    }
    else
    {
        cout<<"NO\n";
    }
    



    return 0;
}