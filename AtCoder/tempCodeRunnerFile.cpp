#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< double > p;
vector< vector<lli> > dp;
lli posibles;
lli n; 


lli f(lli index, lli taken)
{
    if(taken > posibles) return 0;
    if(index == n) return 1;
    if(dp[index][taken] != -1) 
    {
        cout<<dp[index][taken]<<" ";
        return dp[index][taken];
    }

    lli actual = p[index];

    return dp[index][taken] = f(index+1, taken) * actual + f(index+1, taken+1)*(100-actual);
}



int main()
{
    fastIO();
    cin>>n;
    p.resize(n);
    posibles = (n-1)/2;
    dp.assign(n, vector<lli>(1600, -1));
    //dp.assign(n, vector<lli>(1600, -1));
    vector<double> aux(n);
    for(auto &x: aux)
    {
        cin>>x;
    }
    forn(i,0,n)
    {
        p[i] = aux[i] * 100;
    }
    cout<< fixed << setprecision(10) << f(0,0) / pow(100, n) <<endl;
    return 0;
}