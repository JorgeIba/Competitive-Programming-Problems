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

VLL getDigits(lli num)
{
    VLL digits;
    while(num)
    {
        digits.push_back(num%10);
        num/=10;
    }
    reverse(all(digits));
    return digits;
}

VLL digits;
int n;

int dp[10][2][100][100];

int fun(int idx, bool canAll, int sumEven, int sumOdd)
{
    if(idx == n)
    {
        return (sumEven - sumOdd) == 1;
    }

    int digit = digits[idx];
    int limit = canAll? 9 : digit;
    int &ans = dp[idx][canAll][sumEven][sumOdd];
    if(ans != -1) return ans;
    ans = 0;
    int parity = n-idx;
    for(int d = 0; d<=limit; d++)
    {
        if(parity % 2 == 0)
            ans += fun(idx+1, canAll | (d < digit), sumEven+d, sumOdd);
        else
            ans += fun(idx+1, canAll | (d < digit), sumEven, sumOdd+d);
    }
    return ans;
}


int f(int num)
{
    if(num <= 0) return 0;
    digits = getDigits(num);
    n = SZ(digits);
    memset(dp, -1, sizeof(dp));
    //for(auto x: digits) cout << x << " ";
    return fun(0, false, 0, 0);
}


int main () {
	fastIO();
    int t; cin>>t;
    while(t--)
    {
        int l, r; cin>>l>>r;
        cout << f(r) - f(l-1) << endl;
    }
	return 0;
}