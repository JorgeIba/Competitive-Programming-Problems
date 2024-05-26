#include <bits/stdc++.h>

#define endl '\n'
#define fi first
#define se second
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define all(v) v.begin(), v.end()
#define pb push_back
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define var(x) #x << " = " << x

using namespace std;

typedef long long lli;
typedef long double ld;
typedef pair<lli, lli> plli;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<lli>> vvlli;
typedef vector<lli> vlli;
typedef vector<pii> vpii;

int n;
vi primes;
lli mem[300][300];

lli dp(int i, int prv){
	if(primes[i] - primes[prv] > 14) return 0;
	if(primes[i] == n) return 1;
	lli& ans = mem[i][prv];
	if(ans != -1) return ans;
	ans = dp(i + 1, i) + dp(i + 1, prv);
	return ans;
}

int main () {
	fastIO();
	memset(mem, -1, sizeof(mem));
	cin >> n;
	forr(i, 2, 300){
		int cnt = 0;
		forr(j, 2, i - 1)
			if(i % j == 0) cnt++;
		if(cnt == 0) primes.pb(i);
	}
	if(n == 2) cout << 1 << endl;
	else cout << dp(1, 0) << endl;
	return 0;
}

