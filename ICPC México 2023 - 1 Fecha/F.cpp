#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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

int nearestPowerTwo(int n)
{
    int r = 1;
    while(r < n) r<<=1;
    return r;
}

int powerMod(int a, int b, int mod){
	lli res = 1;
	b %= mod-1;
	if(b < 0) b += mod-1;
	while(b){
		if(b & 1) res = (1LL *res * a) % mod;
		b >>= 1;
		a = (1LL * a * a) % mod;
	}
	return res;
}

const int MOD = 998244353;
const int MAXN = 131072;
const int MAXLOG = 18;
const int p = MOD;
const int g = 3;

lli wp[MAXLOG][MAXN], wp_inv[MAXLOG][MAXN];
void prec_ntt() {
    for(int i = 0, n = 1; i < MAXLOG; i++, n <<= 1) {
        lli wk = powerMod(g, (p-1) / (n << 1), p);
        lli wk_inv = powerMod(g, -1 * (p-1) / (n << 1), p);
        wp[i][0] = 1;
        wp_inv[i][0] = 1;
        for(int j = 1; j < MAXN; j++){
            wp[i][j] = wp[i][j-1] * wk % p;
            wp_inv[i][j] = wp_inv[i][j-1] * wk_inv % p;
        }
    }
}

template<int p, int g, typename T>
void ntt(vector<T> & A, bool inv){
	int n = SZ(A);
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(A[i], A[j]);
	}

	for(int k = 1, logg = 0; k < n; k <<= 1, logg++){
		for(int i = 0; i < n; i += k << 1){
			for(int j = 0; j < k; ++j){
				int u = A[i + j], v = (A[i+j+k] * (inv ? wp_inv[logg][j] : wp[logg][j] ) ) % p;
				A[i+j] = (u + v < p) ? u + v : u + v - p;
				A[i+j+k] = (u - v >= 0) ? u - v: u - v + p;
			}
		}
	}

	if(inv){
		lli inv_n = powerMod(n, p - 2, p);
		for(auto &x: A) x = (x*inv_n)%p;
	}
}
 
template<int p = 998244353, int g = 3, typename T>
vector<T> multiply(vector<T> A, vector<T> B){
	int sz = SZ(A) + SZ(B) - 1;
	int size = nearestPowerTwo(sz);
    
	A.resize(size), B.resize(size);
	ntt<p, g>(A, false); ntt<p, g>(B, false);
	for(int i = 0; i < size; i++)
		A[i] = (lli)A[i] * B[i] % p;
	ntt<p, g>(A, true);

	A.resize(sz);
	return A;
}

typedef vector<int> Poly;

Poly operator*(const Poly &A, const Poly &B) {
    return multiply(A, B);
}



vector<int> adjList[MAXN];
bool visited[MAXN];
int sizeSub[MAXN];

inline int getCentroids(int root, int n) {
    int centroid = -1;
    
    auto dfs_ = [&](const auto& dfs_, auto u, auto p) -> void {
        sizeSub[u] = 1;
        bool is_centroid = true;
        for (auto v: adjList[u]){
            if (v == p || visited[v]) continue;
 
            dfs_(dfs_, v, u);
            sizeSub[u] += sizeSub[v];
            if (sizeSub[v] > n / 2) is_centroid = false;
        }
        if (n - sizeSub[u] > n / 2) is_centroid = false;
        if (is_centroid) centroid = u;
    };
    dfs_(dfs_, root, -1);
    return centroid;
}
int nums[MAXN];
int ansArray[2*MAXN];
const int ONE = 1, TWO = 2, TH = 3, FO = 4, FIV = 5;

void dfs_ans(int root_centroid, int n_sz) {
    Poly A(n_sz+1), B(n_sz+1);
    A[0] = nums[root_centroid];
    B[0] = 1;
    visited[root_centroid] = 1;

    auto dfs = [&](const auto &dfs, int u, int dist, int p = -1) -> void{
        A[dist] += nums[u];
        if(A[dist] >= MOD) A[dist] -= MOD;

        B[dist] += 1;

        sizeSub[u] = 1;
        for(auto v: adjList[u]) {
            if(v == p || visited[v]) continue;
            dfs(dfs, v, dist+1, u);
            sizeSub[u] += sizeSub[v];
        }
    };

    for(auto v: adjList[root_centroid]) {
        if(visited[v]) continue;
        dfs(dfs, v, 1, root_centroid);
    }

    Poly almost = A * B;
    for(int i = 0; i < SZ(almost); i++) {
        ansArray[i] = (ansArray[i] + almost[i]);
        if(ansArray[i] >= MOD) ansArray[i] -= MOD;
    }
    

    for(auto v: adjList[root_centroid]) {
        if(visited[v]) continue;

        A.resize(sizeSub[v] + 1);
        B.resize(sizeSub[v] + 1);

        forn(i, SZ(A)) A[i] = 0;
        forn(i, SZ(B)) B[i] = 0;

        dfs(dfs, v, 1, root_centroid);

        Poly sub = A * B;
        for(int i = 0; i < SZ(sub); i++) {
            ansArray[i] = (ansArray[i] - sub[i]);
            if(ansArray[i] < 0) ansArray[i] += MOD;
        }
    }

    
    for(auto v: adjList[root_centroid]) {
        if(visited[v]) continue;
        
        auto centroid_v = getCentroids(v, sizeSub[v]);
    
        dfs_ans(centroid_v, sizeSub[v]);
    }
}


int inv[2*MAXN + 10];

int main(){
    fastIO();

    prec_ntt();

    inv[0] = inv[1] = 1;
    for(lli i = 2; i <= MAXN; ++i){
        inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
	}

    int n; cin>>n;

    forn(i, n) cin>>nums[i];

    for(int i = 0; i < n-1; i++) {
        int u, v; cin>>u>>v; u--, v--;

        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }


    auto centroid = getCentroids(0, n);
    
    dfs_ans(centroid, n);

    int ansT = 0;
    for(int i = 0; i < 2*MAXN; i++){
        ansT += 1LL*ansArray[i] * inv[i+1] % MOD;
        if(ansT >= MOD) ansT -= MOD;
    }

    cout << ansT << endl;

    return 0;
}
