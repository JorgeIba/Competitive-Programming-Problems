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

lli lcm(lli x, lli y)
{
    return (x*y)/(__gcd(x,y));
}


int main () {
	fastIO();
    lli n, m; cin>>n>>m;

    vector<lli> nums(m);
    for(auto &x: nums) cin>>x;

    lli ans = 0;

    for(int mask = 1; mask<(1<<m); mask++)
    {
        lli divisor = 1;
        for(int j = 0; j<m; j++)
        {
            if(mask & (1<<j))
            {
                divisor = lcm(divisor, nums[j]);
            }
        }
        
        if(__builtin_popcount(mask) & 1)
        {
            ans += n/divisor;
        }
        else
        {
            ans -= n/divisor;
        }
    }
    cout << n - ans << endl;
    
	return 0;
}