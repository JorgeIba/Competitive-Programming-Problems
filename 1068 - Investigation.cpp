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

vector<lli> pows10;
const int maxN = 15;

void precPows(lli k)
{
    pows10.resize(maxN); pows10[0] = 1;
    for(int i = 1; i<maxN; i++)
    {
        pows10[i] = (pows10[i-1]*10)%k;
    }
}

lli dp[15][2][150][150];
VLL digits;
int k, n;

lli fun(lli index, bool canAll, lli modulo, lli number)
{
    if(index == n)
    {
        return modulo == 0 && number == 0;
    }
    lli &ans = dp[index][canAll][modulo][number];
    if(ans != -1) return ans;

    ans = 0;
    int limit = canAll? 9: digits[index];
    //cout << n - index - 1 << endl;
    for(int d = 0; d<=limit; d++)
    {
        ans += fun(index+1, canAll | (d < digits[index]), (modulo + d)%k,  (number + pows10[n - index - 1]*d)%k);
    }
    return ans;
    
}

VLL getDigits(lli num)
{
    VLL ans;
    while(num)
    {
        ans.push_back(num%10);
        num/=10;
    }
    reverse(all(ans));
    return ans;
}

lli f(lli num)
{
    if(num <= 0) return 1;
    digits = getDigits(num);
    n = SZ(digits);
    memset(dp, -1, sizeof(dp));
    //cerr << "Ahi te voy\n";
    return fun(0, false, 0, 0);
}


int main () {
	fastIO();
    lli t; cin>>t;
    for(int i = 1; i<=t; i++)
    {
        lli l, r; cin>>l>>r>>k;
        precPows(k);
        cout << "Case " << i << ": " << (k >= 150? 0: f(r) - f(l-1)) << endl;
    }
	return 0;
}