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


// const int MAXN = 23;
// const int MOD = 1e9+7;

// int dp[MAXN + 10][(1<<MAXN) + 10];

// int f(int idx, int mask, const int n){
//     if(idx == n-1) return __builtin_popcount(mask) == n;

//     int &ans = dp[idx][mask];

//     if(ans != -1) return ans;

//     ans = 0;
//     for(int dist = -3; dist <= 3; dist++){
//         int j = idx + dist;
//         if(dist == 0 || j < 0 || j >= n) continue;
    
//         if(~mask & (1 << j)){
//             (ans += f(j, mask ^ (1 << j), n)) %= MOD;
//         }
//     }
//     return ans;
// }

// const int mod = MOD;


// lli inverse(lli a, lli n){
// 	lli r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
// 	while(r1){
// 		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
// 		ri = r0 % r1, r0 = r1, r1 = ri;
// 	}
// 	assert(r0 == 1);
// 	if(s0 < 0) s0 += n;
// 	return s0;
// }

// vector<lli> BerlekampMassey(const vector<lli> & init){
// 	vector<lli> cur, ls;
// 	lli ldd;
// 	for(int i = 0, m; i < init.size(); ++i){
// 		lli eval = 0;
// 		for(int j = 0; j < cur.size(); ++j)
// 			eval = (eval + init[i-j-1] * cur[j]) % mod;
// 		eval -= init[i];
// 		if(eval < 0) eval += mod;
// 		if(eval == 0) continue;
// 		if(cur.empty()){
// 			cur.resize(i + 1);
// 			m = i;
// 			ldd = eval;
// 		}else{
// 			lli k = eval * inverse(ldd, mod) % mod;
// 			vector<lli> c(i - m - 1);
// 			c.push_back(k);
// 			for(int j = 0; j < ls.size(); ++j)
// 				c.push_back((mod-ls[j]) * k % mod);
// 			if(c.size() < cur.size()) c.resize(cur.size());
// 			for(int j = 0; j < cur.size(); ++j){
// 				c[j] += cur[j];
// 				if(c[j] >= mod) c[j] -= mod;
// 			}
// 			if(i - m + ls.size() >= cur.size())
// 				ls = cur, m = i, ldd = eval;
// 			cur = c;
// 		}
// 	}
// 	if(cur.empty()) cur.push_back(0);
// 	reverse(cur.begin(), cur.end());
// 	return cur;
// }


// lli solveRecurrence(const vector<lli> & P, const vector<lli> & init, lli n){
// 	int deg = P.size();
// 	vector<lli> ans(deg), R(2*deg);
// 	ans[0] = 1;
// 	lli p = 1;
// 	for(lli v = n; v >>= 1; p <<= 1);
// 	do{
// 		int d = (n & p) != 0;
// 		fill(R.begin(), R.end(), 0);
// 		for(int i = 0; i < deg; i++)
// 			for(int j = 0; j < deg; j++)
// 				(R[i + j + d] += ans[i] * ans[j]) %= mod;
// 		for(int i = deg-1; i >= 0; i--)
// 			for(int j = 0; j < deg; j++)
// 				(R[i + j] += R[i + deg] * P[j]) %= mod;
// 		copy(R.begin(), R.begin() + deg, ans.begin());
// 	}while(p >>= 1);
// 	lli nValue = 0;
// 	for(int i = 0; i < deg; i++)
// 		(nValue += ans[i] * init[i]) %= mod;
// 	return nValue;
// }

vector<lli> init = {1, 1, 1, 2, 6, 14, 28, 56, 118, 254, 541, 1140, 2401, 5074, 10738, 22711, 48001, 101447, 214446, 453355, 958395, 2025963, 4282685};

int main () {
	//fastIO();
	
    // for(int n = 1; n <= MAXN; n++){
    //     memset(dp, -1, sizeof(dp));

    //     cout << f(0, 1, n) << ", ";
    // }
    // cout << endl;


    // auto P = BerlekampMassey(init);

    // for(auto x: P) cout << x << " ";
    // cout << endl;

    // cout << solveRecurrence(P, init, 39) << endl;


    const int MOD = 1e9;

    lli neg = MOD-1;

    vector<lli> P = {neg, neg, 0, 1, 1, 2, neg, 2};
    vector<lli> init = {1, 1, 1, 2, 6, 14, 28, 56};

    reverse(all(P));

    int n = 1e6-1;
    vector<lli> f(n+2);

    for(int i = 0; i < SZ(init); i++)
        f[i] = init[i];


    for(int i = SZ(init); i <= n; i++){
        for(int j = 1; j <= 8; j++){
            (f[i] += f[i-j]*P[j-1] % MOD) %= MOD;
        }
    }

    lli sum = 0;
    forr(i, 0, n) (sum += f[i]*f[i]%MOD*f[i]%MOD) %= MOD;
    cout << sum << endl;



    // for(int n = 1; n <= 40; n++){
    //     cout << solveRecurrence(P, init, n) << " ";
    // }
    // cout << endl;


	return 0;
}

