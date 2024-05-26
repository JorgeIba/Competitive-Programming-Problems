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


const int MOD = 10007;
const int mod = MOD;
const int MAXN = 1600;
const int MAXS = 200;

int kthTermLinearRecurrence(const vector<int> & P, const vector<int> & init, lli n){
	int deg = P.size();
	vector<int> ans(deg), R(2*deg);
    ans[0] = 1;

	int p = 1;
	for(lli v = n; v >>= 1; p <<= 1);
	do{
		int d = (n & p) != 0;
		fill(R.begin(), R.end(), 0);
		for(int i = 0; i < deg; i++)
			for(int j = 0; j < deg; j++) {
                R[i + j + d] = (R[i + j + d] + ans[i] * ans[j] % MOD);
                if(R[i+j+d] >= MOD) R[i+j+d] -= MOD;
            }
				
		for(int i = deg-1; i >= 0; i--)
			for(int j = 0; j < deg; j++) {
                R[i + j] = (R[i + j] +  R[i + deg] * P[j] % MOD);
                if(R[i+j] >= MOD) R[i+j] -= MOD;
            }

		copy(R.begin(), R.begin() + deg, ans.begin());
	}while(p >>= 1);

	int nValue = 0;
	for(int i = 0; i < deg; i++){
        nValue = (nValue +  ans[i] * init[i] % MOD);
        if(nValue >= MOD) nValue -= MOD;
    }
	return nValue;
}

int inverse(int a, int n){
	int r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	assert(r0 == 1);
	if(s0 < 0) s0 += n;
	return s0;
}

vector<int> BerlekampMassey(const vector<int> & init){
	vector<int> cur, ls;
	int ldd;
	for(int i = 0, m; i < SZ(init); ++i){
		int eval = 0;
		for(int j = 0; j < SZ(cur); ++j)
			eval = (eval + init[i-j-1] * cur[j]) % mod;
		eval -= init[i];
		if(eval < 0) eval += mod;
		if(eval == 0) continue;
		if(cur.empty()){
			cur.resize(i + 1);
			m = i;
			ldd = eval;
		}else{
			int k = eval * inverse(ldd, mod) % mod;
			vector<int> c(i - m - 1);
			c.push_back(k);
			for(int j = 0; j < SZ(ls); ++j)
				c.push_back((mod-ls[j]) * k % mod);
			if(c.size() < cur.size()) c.resize(cur.size());
			for(int j = 0; j < SZ(cur); ++j){
				c[j] += cur[j];
				if(c[j] >= mod) c[j] -= mod;
			}
			if(i - m + ls.size() >= cur.size())
				ls = cur, m = i, ldd = eval;
			cur = c;
		}
	}
	if(cur.empty()) cur.push_back(0);
	reverse(cur.begin(), cur.end());
	return cur;
}


int dp[MAXN+10][MAXS+10][MAXS+10];

string s; 
int f(lli n, int l, int r) {
    if(n == 0) {
        if(l > r) return 1;
        return 0;
    }
    if(n == 1) {
        if(l > r) return 26;
        return l == r;
    } 

    int &ans = dp[n][l][r];
    if(ans != -1) return ans;

    ans = 0;

    for(char c = 'a'; c <= 'z'; c++) {
        if(l > r) {
            ans += f(n-2, l, r);
        } else {
            ans += f(n-2, l + (s[l] == c), r - (s[r] == c));
        }
        if(ans >= MOD) ans -= MOD;
    }    

    return ans;
}


int main () {
	fastIO();
	
    cin>>s;
    lli n; cin>>n;

    memset(dp, -1, sizeof(dp));
    vector<int> init;
    for(int m = 0; m <= MAXN; m++)
        init.push_back(f(m, 0, SZ(s) - 1));
        
    auto recurrence = BerlekampMassey(init);
    init.resize(SZ(recurrence));

    auto ans = kthTermLinearRecurrence(recurrence, init, n + SZ(s));

    cout << ans << endl;
    
	return 0;
}

