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

int k, n;
VI digits;
VLL pows10;
const lli MOD = 998244353;
VI getDigits(lli num)
{
    VI digits;
    while(num)
    {
        digits.push_back(num % 10);
        num/=10;
    }
    reverse(all(digits));
    return digits;
}

void prec()
{
    pows10.resize(21, 1);
    for(int i = 1; i<21; i++)
    {
        pows10[i] = (pows10[i-1]*10)%MOD;
    }
}

lli dp[2][20][2][2][1<<11];

lli fun(lli idx, bool canAll, bool prefixZeros, lli mask)
{
    if(idx == n) 
    {
        return __builtin_popcount(mask) <= k;
    }
    int digit = digits[idx];
    int limit = canAll? 9: digit;

    lli &ans = dp[0][idx][canAll][prefixZeros][mask];
    if(ans != -1) return ans;
    ans = 0;

    for(int d = 0; d<=limit; d++)
    {
        if(prefixZeros && d == 0)
            ans += fun(idx+1, canAll | (d < limit), true, mask);
        else
            ans += fun(idx+1, canAll | (d < limit), false, mask | (1<<d));
        if(ans >= MOD) ans-=MOD;
    }
    return ans;
}

lli funCount(lli idx, bool canAll, bool prefixZeros, lli mask)
{
    if(idx == n) 
        return 0;
    int digit = digits[idx];
    int limit = canAll? 9: digit;

    lli &ans = dp[1][idx][canAll][prefixZeros][mask];
    if(ans != -1) return ans;
    ans = 0;

    for(int d = 0; d<=limit; d++)
    {
        if(prefixZeros && d == 0)
            ans = (ans + d*pows10[n-idx-1]*fun(idx+1, canAll | (d < limit), true, mask) + funCount(idx+1, canAll | (d < limit), true, mask))%MOD;
        else
            ans = (ans + d*pows10[n-idx-1]*fun(idx+1, canAll | (d < limit), false, mask | (1<<d)) + funCount(idx+1, canAll | (d < limit), false, mask | (1<<d)))%MOD;
    }
    return ans%MOD;
}

lli f(lli num)
{
    if(num <= 0) return 0;
    digits = getDigits(num);
    n = SZ(digits);
    memset(dp, -1, sizeof(dp));
    fun(0, false, true, 0);
    return funCount(0, false, true, 0);
}


int main () {
	//fastIO();
    prec();
    lli l, r; cin>>l>>r>>k;
    lli ans = f(r);
    ans -= f(l-1);

    cout << (ans < 0 ? ans+MOD: ans) << endl;

	return 0;
}