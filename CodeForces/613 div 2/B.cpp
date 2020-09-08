#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void solve()
{
    lli n; cin>>n;
    lli total = 0;
    vector<lli> tastes(n);
    for(int i=0; i<n; i++)
    {
        cin>>tastes[i];
        total+=tastes[i];
    }
    lli best1 = 0, sum1 = 0;
    for(int k=1; k<n; k++)
    {
        sum1 = max(tastes[k], sum1 + tastes[k]);
        best1 = max(best1, sum1);
    }
    lli best2 = 0, sum2 = 0;
    for(int k=0; k<n-1; k++)
    {
        sum2 = max(tastes[k], sum2 + tastes[k]);
        best2 = max(best2, sum2);
    }

    lli best = max(best1, best2);

    //cout<<best<<endl;
    if(best < total)
    {
        cout<<"YES\n";
    }
    else
    {
        cout<<"NO\n";
    }
}



int main()
{
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}