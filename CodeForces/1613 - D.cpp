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

const lli MOD = 998244353;
const lli maxN = 5e5+10;
lli dp[maxN][3][2][2];

vector<lli> nums, next_equal, next_pone, next_ptwo, next_mtwo;

lli f(lli idx, lli type, bool mayor, bool equal)
{
    if(idx == -1) return 0;


    lli &ans = dp[idx][type][mayor][equal];

    if(ans != -1) return ans;

    if(equal)
    {
        lli only_take = f(idx, type, mayor, false);
        lli more = f(next_equal[idx], type, mayor, true);
        return ans = only_take + more;
    }



    ans = 1;
    if(type == 1) // igual o seguido o dos
    {
        lli equal = f(next_equal[idx], 1, false, true), seguido = f(next_pone[idx], 1, false, true), jumping = f(next_ptwo[idx], 2, true, true);
        ans += (equal + seguido + jumping) % MOD;
    }
    else { //igual o menos dos o mas dos
        lli equal = f(next_equal[idx], 2, mayor, true), to_less = 0, to_more = 0;
        if(mayor)
        {
            to_less = f(next_mtwo[idx], 2, false, true);
        }
        else {
            to_more = f(next_ptwo[idx], 2, true, true);
        }
        ans += (equal + to_less + to_more)%MOD;
    }

    if(ans >= MOD) ans -= MOD;
    // cout << ans << endl;
    return ans;
}


void solve()
{
    lli n; cin>>n;

    for(int i = 0; i<n+10; i++)
    {
        for(int j = 0; j<3; j++)
        {
            for(int k = 0; k<2; k++)
            {
                for(int l = 0; l<2; l++)
                {
                    dp[i][j][k][l] = -1;
                }
            }
        }
    }


    nums.resize(n);
    next_equal.resize(n);
    next_pone.resize(n);
    next_ptwo.resize(n);
    next_mtwo.resize(n);
    for(auto &x: nums) cin>>x;


    map<lli,lli> last;
    for(int i = n-1; i>=0; i--)
    {
        lli num = nums[i];
        next_equal[i] = last.count(num) ? last[num] : -1;
        next_pone[i] = last.count(num+1) ? last[num+1] : -1;
        next_ptwo[i] = last.count(num+2) ? last[num+2] : -1;
        next_mtwo[i] = last.count(num-2) ? last[num-2] : -1;

        last[num] = i;
    }

    lli ans = (last.count(0) ? f(last[0], 1, false, true) : 0) + (last.count(1) ? f(last[1], 2, true, true) : 0);

    cout << ans % MOD << endl;

}



int main () {
	fastIO();
    lli t; cin>>t;

    while(t--) solve();

	return 0;
}

