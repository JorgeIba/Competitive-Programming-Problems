#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli dp[5005][5005]; 
const lli MOD = 1e9+7;

lli fun(lli s, lli b)
{
    if(s < 0 || b < 0) return 0;
    if(b == 1) return 1;
    if(s == 0) return 0;
    lli &res = dp[s][b];
    if(res != -1) return res;
    res = (fun(s, b-s) + 2*fun(s-1, b) - fun(s-2, b))%MOD;
    if(res < 0) res += MOD;
    return res;
}

int main () {
	//fastIO();
    memset(dp, -1, sizeof(dp));
	lli s,b; cin >> s >> b;
    cout << fun(s, b-s+1) << endl;

	return 0;
}
