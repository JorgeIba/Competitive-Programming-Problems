#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli solve()
{
    lli n; cin>>n;
    vector<lli> pares, impares;
    for(int i = 0; i<2*n; i++)
    {
        lli x; cin>>x;
        if(x & 1) impares.push_back(i+1);
        else pares.push_back(i+1);
    }
    lli size = impares.size();
    if(size > 0)
    {
        if(~impares.size() & 1)
        {
            impares.pop_back();
            impares.pop_back();
        }
        else
        {
            impares.pop_back();
            pares.pop_back();
        }
    }

    vector< lli > ans;
    for(int i = 0; i<impares.size(); i++)
    {
        ans.push_back(impares[i]);
    }
    for(int i = 0; i<pares.size(); i++)
    {
        ans.push_back(pares[i]);
    }
    //cout<< "PTM "<< n-1 << endl;
    for(int i = 0; i<2*(n-1); i+=2)
    {
        cout<< ans[i] << " " << ans[i+1]<<endl;
    }
    
    
    
}



int main()
{
    //fastIO();
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }

    return 0;
}