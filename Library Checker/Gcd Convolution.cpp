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


const int MOD = 998244353;

// Calculate array G
// g_d = a_i * b_j where gcd(i, j) = d
// a and b are 1-indexed
// forr(i, 1, n)
//   forr(j, 1, n)
//     g[gcd(i, j)] += a[i]*b[j]
// O(n log n)
template<typename T, int mod = MOD>
vector<T> gcdConvolution(const vector<T> &a, const vector<T> &b) {
    int n = SZ(a);

    vector<T> A(n+1), B(n+1), G(n+1);
    for(int g = 1; g <= n; g++) {
        for(int k = g; k <= n; k += g) {
            A[g] = (A[g] + a[k-1]) % mod;
            B[g] = (B[g] + b[k-1]) % mod;
        }
        G[g] = 1LL * A[g] * B[g] % mod;
    }

    vector<T> dp_g(n);
    for(int i = n; i >= 1; i--) {

        dp_g[i-1] = G[i];

        for(int k = 2*i; k <= n; k += i) {
            dp_g[i-1] = (dp_g[i-1] - dp_g[k-1] + mod) % mod;
        }
    }
    return dp_g;
}


int main () {
	fastIO();
    
    int n; cin>>n;
    vector<int> A(n), B(n);

    for(auto &x: A) cin>>x;
    for(auto &x: B) cin>>x;


    auto C = gcdConvolution(A, B);
    for(auto c: C) cout << c << " ";
    cout << endl;

	return 0;
}

