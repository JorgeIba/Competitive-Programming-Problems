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

const int n = 40;

lli dp[41][2][10][(1<<11)];

lli fun(int idx, bool prefixZero, int last, int mask)
{
    if(idx == n)
    {
        return __builtin_popcount(mask) == 10;
    }

    lli &ans = dp[idx][prefixZero][last][mask];
    if(ans != -1) return ans;
    ans = 0;

    for(int d = 0; d<=9; d++)
    {
        if(prefixZero)
        {
            if(d == 0)
            {
                ans += fun(idx+1, true, 0, 0);
            }
            else
            {
                ans += fun(idx+1, false, d, (mask | (1<<d)));
            }
        }
        else
        {
            if(abs(last - d) == 1)
            {
                ans += fun(idx+1, false, d, (mask | (1<<d)));
            }
        }
        
    }
    return ans;
}



int main () {
	//fastIO();
    memset(dp, -1, sizeof(dp));

    cout << fun(0, true, 0, 0) << endl;

	return 0;
}