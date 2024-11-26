#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;


const int MAXN = 3000 + 100;
const int MAXVALD = 2*MAXN + 50;
const int MOD = 1e9 + 7;


vector<int> adjList[MAXN];

int dp[MAXN][MAXVALD];

template <typename T>
T kthTermLinearRecurrence(const vector<T> &P, const vector<T> &init, lli n) {

    int deg = P.size();
    vector<T> ans(deg), R(2 * deg);
    ans[0] = 1; // Multiplicative Neutro

    int p = 1;
    for (lli v = n; v >>= 1; p <<= 1);
    do {
        int d = (n & p) != 0;
        fill(R.begin(), R.end(), T());
        for (int i = 0; i < deg; i++)
            for (int j = 0; j < deg; j++){
                R[i + j + d] = (R[i + j + d] + 1LL * ans[i] * ans[j] % MOD);
                if(R[i + j + d] >= MOD) R[i + j + d] -= MOD;
            }
                
        for (int i = deg - 1; i >= 0; i--)
            for (int j = 0; j < deg; j++) {
                R[i + j] = (R[i + j] + 1LL * R[i + deg] * P[j] % MOD);
                if(R[i + j] >= MOD) R[i + j] -= MOD;
            }
                

        copy(R.begin(), R.begin() + deg, ans.begin());
    } while (p >>= 1);

    T nValue = T();
    for (int i = 0; i < deg; i++){
        nValue = (nValue + 1LL * ans[i] * init[i] % MOD);
        if(nValue >= MOD) nValue -= MOD;
    }
        
    return nValue;
}

lli inverse(lli a, lli n){
	lli r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	assert(r0 == 1);
	if(s0 < 0) s0 += n;
	return s0;
}
//Finds the shortest linear recurrence relation for the
//given init values. Only works for prime modulo.
vector<int> BerlekampMassey(const vector<int> & init){
	vector<int> cur, ls;
	int ld;
	for(int i = 0, m; i < (int)init.size(); ++i){
		int eval = 0;
		for(int j = 0; j < (int)cur.size(); ++j)
			eval = (eval + 1LL * init[i-j-1] * cur[j]) % MOD;
		eval -= init[i];
		if(eval < 0) eval += MOD;

		if(eval == 0) continue;
		if(cur.empty()){
			cur.resize(i + 1);
			m = i;
			ld = eval;
		}else{
			int k = 1LL * eval * inverse(ld, MOD) % MOD;
			vector<int> c(i - m - 1);
			c.push_back(k);
			for(int j = 0; j < (int)ls.size(); ++j)
				c.push_back(1LL * (1LL * MOD-ls[j]) * k % MOD);
			if(c.size() < cur.size()) c.resize(cur.size());
			for(int j = 0; j < (int)cur.size(); ++j){
				c[j] += cur[j];
				if(c[j] >= MOD) c[j] -= MOD;
			}
			if(i - m + ls.size() >= cur.size())
				ls = cur, m = i, ld = eval;
			cur = c;
		}
	}
	if(cur.empty()) cur.push_back(0);
	reverse(cur.begin(), cur.end());
	return cur;
}


int main () {
	fastIO();

    int n, D; cin>>n>>D;

    forr(i, 1, n-1) {
        int p; cin>>p; p--;
        adjList[p].push_back(i);
    }

    memset(dp, -1, sizeof(dp));
    auto f = [&](const auto &f, int u, int score) {
        if(score == 0) return 0;

        int &ans = dp[u][score];
        if(ans != -1) return ans;
    
        int yes = 1, no = f(f, u, score-1);

        for(auto v: adjList[u]) {
            int ans_v = f(f, v, score);
            yes = 1LL * yes * ans_v % MOD;
        }

        ans = (yes + no) % MOD;

        return ans;
    };

    vector<int> vals;

    int ans = 0;
    for(int i = 1; i <= min(D, 2*(n+1)); i++) {
        ans = f(f, 0, i);
        if(ans >= MOD) ans -= MOD;
        vals.push_back(ans);
    }

    if(SZ(vals) == D) {
        cout << vals.back() << endl;
    } else {

        auto recurrence = BerlekampMassey(vals);

        // debugg(SZ(vals));

        vals.resize(SZ(recurrence));
        auto ans = kthTermLinearRecurrence(recurrence, vals, D-1);

        // debugg(SZ(vals));
        // debugg(SZ(recurrence)); 
        // Recurrence alwasys needs 2*(n+1) evaluations
        // Mmmmm polynomial?

        cout << ans << endl;
    }


	return 0;
}

