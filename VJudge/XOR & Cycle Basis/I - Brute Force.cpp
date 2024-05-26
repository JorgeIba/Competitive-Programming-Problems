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

const int LOG_D = 36;
vector<lli> basis(LOG_D); 
lli sz_basis = 0;

void insert_vector(lli mask, bool zeros = false) //Zeros -> make zeros above basis[i]
{
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

const int MOD = 998244353;

lli powerMod(lli a, lli b){
	lli res = 1;
	while(b){
		if(b&1) res = res * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}
	return res;
}


struct DP{
	int ways[LOG_D];

	DP(){
		memset(ways, 0, sizeof(ways));
	}

	DP(int x){
		memset(ways, 0, sizeof(ways));
		ways[x]++;
	}

	DP operator+(const DP &y){
		DP aux;
		forn(i, LOG_D){
			aux.ways[i] = (ways[i] + y.ways[i]) % MOD;
		}
		return aux;
	}
};

const int MAXM = 35;
const int HALF_M = 17;
DP dp[HALF_M + 5][(1LL << HALF_M) + 100];
bool visited[HALF_M + 5][(1LL << HALF_M) + 100];

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
	//fastIO();

	cin>>n>>m;

	vector<lli> nums(n);
	for(auto &x: nums) cin>>x;


    vector<lli> total_ans(m+1);
    for(int mask = 0; mask < (1 << n); mask++){
        lli total_xor = 0;
        for(int j = 0; j < n; j++){
            if(mask & (1 << j)) {
                total_xor ^= nums[j];
            }
        }

        int score = __builtin_popcountll(total_xor);
        total_ans[score]++;
    }

    for(auto x: total_ans) cout << x << " ";
    cout << endl;

	return 0;
}

