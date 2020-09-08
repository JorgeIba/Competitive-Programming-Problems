#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

const lli MOD = 1000000007;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    lli n, m; cin>>n>>m;
    vector< string > names(n);
    for(auto &x: names)
    {
        cin>>x;
    }
    vector<lli> diferents(m);
    for(int i = 0; i < m; i++ )
    {
        set<char> diff;

        for(int j = 0; j<n; j++)
        {
            char c = names[j][i];
            if( diff.find(c) == diff.end())
            {
                diff.insert(c);
            }
        }
        diferents[i] = diff.size();
    }
    lli res = 1;
    for(auto x: diferents)
    {
        res = (res*x) % MOD;
    }
    cout<<res<<endl;

    
    

    return 0;
}