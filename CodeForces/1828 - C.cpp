#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;


const lli MAXN = 1e6;
const lli MOD = 1e9+7;
vector<lli> fact(MAXN+1, 1), inv(MAXN+1, 1), invFact(MAXN+1,1);
void prec()
{
    for(lli i = 2; i <= MAXN; ++i){
        fact[i] = i*fact[i-1] %MOD;
        inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
        invFact[i] = inv[i]*invFact[i-1]%MOD;
	}
}

lli nCr(lli n, lli r) {
    if(n < 0 || r > n || r < 0) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n-r] % MOD;
}


void main_(){
	int n; cin>>n;
    vector<int> a(n), b(n);

    for(auto &x: a) cin>>x;
    for(auto &x: b) cin>>x;
    
    sort(all(a));
    sort(all(b));

    vector<int> cnt_pos(n+1);
    for(int i = 0; i < n; i++){
        int pos = upper_bound(all(b), a[i]-1) - begin(b);
        cnt_pos[pos]++;
    }

    if(cnt_pos[0]) {
        cout << 0 << endl;
        return;
    }


    lli ans = 1;
    int cnt = 0;
    forr(i, 1, n) {
        lli total = nCr(i - cnt, cnt_pos[i]) * fact[cnt_pos[i]] % MOD;
        ans = ans * total % MOD;
        cnt += cnt_pos[i];
    }

    cout << ans << endl;
}


int main () {
	fastIO();

    prec();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

