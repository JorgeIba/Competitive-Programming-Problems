#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,n) for(int i = a; i <= n; i++)
#define all(v) v.begin(), v.end()
#define se second
#define fi first
#define pb push_back
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
 
using namespace std; 

typedef pair<lli, lli> plli;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<lli>> vvlli;
typedef vector<lli> vlli;
typedef vector<pii> vpii;
const lli maxN = 1e6;
const lli MOD = 1e9+7;
const lli mod = 1e9+7;
vector<lli> fact(maxN+1, 1), inv(maxN+1, 1), invFact(maxN+1,1);
void prec()
{
    for(lli i = 2; i < maxN; ++i)
    {
        fact[i] = i*fact[i-1] %MOD;
        inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
        invFact[i] = (lli)inv[i]*invFact[i-1]%MOD;
    }
}
 
lli comb(lli n, lli r){
	if(r < 0 || r > n) return 0;
    return ((fact[n]*invFact[n-r]%MOD)*invFact[r])%MOD;
}
lli A, B, C, c, K;
int main(){
	fastIO();
	prec();
	int tt;
	cin >> tt;
	while(tt--){
		cin >> A >> B >> C >> K >> c;
		if(K-c < 2) {
			cout << "0\n";
			continue;
		}
		if(B + A < K - c){
			cout << "0\n";
			continue;
		}
		lli ans = ((comb(A+B, K - c)-comb(B, K-c)+mod)%mod - comb(A, K-c) + mod)%mod;
		ans = (ans*comb(C, c))%mod;
		cout << ans << '\n';
	}
	return 0;
}

