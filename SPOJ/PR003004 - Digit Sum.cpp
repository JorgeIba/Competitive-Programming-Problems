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


VI getDigits(lli num)
{
    VI digits;
    while(num)   
    {
        digits.push_back(num%10);
        num/=10;
    }
    reverse(all(digits));
    return digits;
}


VI digits;
int n;

lli dp[20][2][150]; // suma al estar en el i-esimo indice

lli fun(int idx, bool canAll, lli sum)
{
    if(idx == n) return sum;

    int digit = digits[idx];
    int limit = canAll? 9 : digit;
    lli &ans = dp[idx][canAll][sum];
    if(ans != -1) return ans;
    ans = 0;
    for(int d = 0; d<=limit; d++)
    {
        ans += fun(idx+1, canAll | (d < limit), sum + d);
    }
    return ans;
}

lli f(lli num)
{
    if(num<=0) return 0;
    digits = getDigits(num);
    n = SZ(digits);
    memset(dp,  -1, sizeof(dp));
    return fun(0, false, 0);
}

void solve()
{
    lli a, b; cin>>a>>b;
    cout << f(b) - f(a-1) << endl;
}


int main () {
	fastIO();
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
	return 0;
}