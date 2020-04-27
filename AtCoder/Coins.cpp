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
vector< vector<double> > dp;
lli posibles;
lli n; 
 
double eps = 1e-9;
 
double f(lli index, lli taken)
{
    if(taken > posibles) return 0;
    if(index == n) return (double)1;

    if( dp[index][taken] != -1) return dp[index][taken];
 
    double actual = p[index];
    //dp[index][taken] = 1;
 
    return dp[index][taken] = f(index+1, taken) * actual + f(index+1, taken+1)*(1-actual);
}
 
 
 
int main()
{
    fastIO();
    cin>>n;
    p.resize(n);
    posibles = (n-1)/2;
    dp.assign(n, vector<double>(3000, -1));
    for(double &x: p)
        cin>>x;
    cout<< fixed << setprecision(10) << f(0,0) <<endl;
    return 0;
}