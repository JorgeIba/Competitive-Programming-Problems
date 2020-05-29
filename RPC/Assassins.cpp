#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< double> dp[1000][1000];
vector< pair<lli,lli> > atte;

lli funcion(lli contra, bool muerto)


int main()
{
    //fastIO();
    lli n, m; cin>>n>>m;
    atte.resize(n);
    for(auto x: atte)
    {
        cin>>x.first<<" "<<x.second;
    }
    cout<<funcion(atte[0].second)

    


    return 0;
}