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

const int LOG_D = 35;
vector<lli> basis(LOG_D); 
lli sz_basis = 0;

void insert_vector(lli mask, bool zeros = false) {
    for(int i = LOG_D-1; i>=0; i--){
        if(!(mask & (1LL<<i))) continue;

        if(!basis[i]){
            basis[i] = mask;
			sz_basis++;

			if(!zeros) return;

			for(int j = 0; j<LOG_D; j++){
				if(j==i) continue;
				if(j < i){
					if(basis[i] & (1LL << j)) basis[i] ^= basis[j];
				}
				else{
					if(basis[j] & (1LL << i)) basis[j] ^= basis[i];
				}
			}
            return;
        }
        mask ^= basis[i];
    }
}

const int MOD = 998'244'353;

lli powerMod(lli a, lli b){
	lli res = 1;
	while(b){
		if(b&1) res = res * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}
	return res;
}

const int MAXM = LOG_D;
const int HALF_M = MAXM/2;

struct DP{
	int ways[HALF_M+1];

	DP(){
		memset(ways, 0, sizeof(ways));
	}

	DP(int x){
		memset(ways, 0, sizeof(ways));
		ways[x]++;
	}

	DP operator+(const DP &y){
		DP aux;
		forn(i, HALF_M+1){
			aux.ways[i] = (ways[i] + y.ways[i]) % MOD;
		}
		return aux;
	}
};


DP dp[HALF_M + 2][(1LL << HALF_M) + 10];
bool visited[HALF_M + 2][(1LL << HALF_M) + 10];

int n, m; 

DP f(int idx, lli mask){
	if(idx == -1) {
		int score = __builtin_popcountll(mask);
		return DP(score);
	}

	if(visited[idx][mask]) return dp[idx][mask];
	visited[idx][mask] = true;

	if(basis[idx]){
		DP yes = f(idx-1, mask ^ basis[idx]);
		DP no  = f(idx-1, mask);
		return dp[idx][mask] = yes + no;
	} else {
		DP no  = f(idx-1, mask);
		return dp[idx][mask] = no;
	}
}


int main () {
	fastIO();

	cin>>n>>m;

	vector<lli> nums(n);
	for(auto &x: nums) cin>>x;

	for(auto x: nums)
		insert_vector(x, true);


	int half = LOG_D/2;
	vector<lli> valid;
	for(int i = LOG_D-1; i >= half; i--){
		if(basis[i])
			valid.push_back(basis[i]);
	}
	int sz_gr = SZ(valid);


	lli pref = (1LL << half) - 1;
	lli suff = (~0 & (~pref));


	vector<int> total_ans(2*(MAXM+1));
	for(int mask = 0; mask < (1 << sz_gr); mask++){
		lli xor_total = 0;
		
		for(int j = 0; j < sz_gr; j++){
			if(mask & (1LL << j)) {
				xor_total ^= valid[j];
			}
		}

		DP others = f(half-1, xor_total & pref);
		int score_first = __builtin_popcountll(xor_total & suff);
		
		for(int i = 0; i <= HALF_M; i++){
			(total_ans[i + score_first] += others.ways[i]) %= MOD;
		}
	}

	int kernel = n - sz_basis;

	forn(i, m+1) cout << total_ans[i] * powerMod(2, kernel) % MOD << " ";
	cout << endl;


	return 0;
}

