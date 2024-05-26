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
void prec(){
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

const int INF = 1e9+10;

int main () {
	//fastIO();

    prec();
	
    int n, k; cin>>n>>k;
    vector< pair<int,int> > queries(n);

    for(auto &[l, r]: queries) cin>>l>>r;

    vector<int> all_vals;  
    for(auto [l, r]: queries){
        all_vals.push_back(l);
        // all_vals.push_back(r);
        all_vals.push_back(r+1);
    }

    sort(all(all_vals));

    map<int,int> map_to_comp, map_to_ori;
    auto mapp = [&](int x){
        if(!map_to_comp.count(x)) {
            int idx = SZ(map_to_comp);
            map_to_comp[x] = idx;
            map_to_ori[idx] = x;
        }
        return map_to_comp[x];
    };

    for(auto x: all_vals) mapp(x);

    int m = SZ(map_to_comp);

    vector<int> prefix(m);

    for(auto [l, r]: queries){
        prefix[mapp(l)] += 1;
        prefix[mapp(r+1)] -= 1;
    }

    lli ans = 0;
    lli sum = 0;
    lli last = map_to_ori[0];
    for(int i = 0; i < m; i++){
        auto ori = map_to_ori[i];

        (ans += 1LL*(ori - last) * nCr(sum, k) % MOD) %= MOD;
        sum += prefix[i];
        last = ori;
    }
    cout << ans << endl;

	return 0;
}

