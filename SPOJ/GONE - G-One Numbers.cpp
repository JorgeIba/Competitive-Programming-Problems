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

vector<bool> isPrime;
void primesSieve(int n)
{
	isPrime.resize(n + 1, true);
	isPrime[0] = isPrime[1] = false;
	for(int i = 4; i <= n; i += 2) isPrime[i] = false;
	for(lli i = 3; i <= n; i += 2)
    {
		if(isPrime[i])
        {
			if(i * i <= n)
				for(int j = i * i; j <= n; j += 2 * i)
					isPrime[j] = false;
		}
	}
}


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

int dp[10][2][100];

int fun(int idx, bool canAll, int sum)
{
    if(idx == n)
    {
        return isPrime[sum];
    }

    int digit = digits[idx];
    int limit = canAll? 9 : digit;
    int &ans = dp[idx][canAll][sum];
    if(ans != -1) return ans;
    ans = 0;
    for(int d = 0; d<=limit; d++)
    {
        ans += fun(idx+1, canAll | (d < digit), sum+d);
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
    return fun(0, false,0);
}


int main () {
	fastIO();
    primesSieve(100);
    int t; cin>>t;
    while(t--)
    {
        int l, r; cin>>l>>r;
        cout << f(r) - f(l-1) << endl;
    }
	return 0;
}