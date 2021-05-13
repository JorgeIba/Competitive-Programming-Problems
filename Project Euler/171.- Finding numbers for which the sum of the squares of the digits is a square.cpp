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

/*
    %10 = last digit
    %100 = last 2 digits
    %1000 = last 3 digits
    %10^x = last x digits
*/

const int n = 20;
const int MOD = 1e9;


vector<lli> pows10;
lli dp[2][21][10000];

void precPows(int n)
{
    pows10.resize(n+1, 1);
    for(int i = 1; i<=n; i++)
    {
        pows10[i] = (pows10[i-1]*10)%MOD;
    }
}

bool isPerfect(lli num)
{
    ld sr = sqrt(num);
    return ((sr - floor(sr)) == 0);
}

lli counting(int idx, int sum)
{
    if(idx == n)
    {
        return isPerfect(sum);
    }

    lli &ans = dp[0][idx][sum];
    if(ans != -1) return ans;
    ans = 0;

    for(int d = 0; d<=9; d++)
    {
        ans += counting(idx+1, sum + d*d);
    }
    return ans;
}

lli adding(int idx, int sum)
{
    if(idx == n) return 0;

    lli &ans = dp[1][idx][sum];
    if(ans != -1) return ans;
    ans = 0;
    for(int d = 0; d<=9; d++)
    {
        ans = (ans + ((d*pows10[n-idx-1]*counting(idx+1, sum+d*d))%MOD)%MOD + adding(idx+1, sum + d*d)) % MOD;;
    }

    return ans;
}


int main () {
	//fastIO();
    precPows(21);
    memset(dp, -1, sizeof(dp));
    counting(0, 0);
    cout << adding(0, 0) << endl;

	return 0;
}