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

int n, m; 
VI setNumbers;

lli dp[10][10];

lli fun(int idx, int last)
{
    if(idx == m)
        return 1;

    lli ans = dp[idx][last];
    if(ans != -1) return ans;
    ans = 0;
    for(auto d: setNumbers)
    {
        if(idx == 0)
        {
            ans += fun(idx+1, d);
        }
        else
        {
            if(abs(d - last) <= 2)
            {
                ans+= fun(idx+1, d);
            }
        }
    }
    return ans;
}



lli solve()
{
    cin>>n>>m;
    VI setNumbersAux;
    for(int i = 0; i<n; i++)
    {
        int d; cin>>d;
        setNumbersAux.push_back(d);
    }
    setNumbers = setNumbersAux;
    memset(dp, -1, sizeof(dp));
    return fun(0, 0);
}


int main () {
	fastIO();
    int t; cin>>t;
    for(int i = 1; i<=t; i++)
    {
        cout << "Case " << i << ": " << solve() << endl;
    }

	return 0;
}