#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

lli dp[105][105][105];

lli f(lli n, lli idx, lli k)
{
    if(n == 0)
    {
        return k >=2 ;
    }
    else if(n < 0) return 0;

    if(idx > n) return 0;

    if(dp[n][idx][k] != -1) return dp[n][idx][k];

    lli tomar = f(n-idx, idx, k+1);
    lli no_tomar = f(n, idx+1, k);
    
    return dp[n][idx][k] = tomar + no_tomar;
}


int main () {
	//fastIO();
    lli n; cin>>n;
    memset(dp, -1, sizeof(dp));

    cout << f(n, 1, 0) << endl;
    
	return 0;
}