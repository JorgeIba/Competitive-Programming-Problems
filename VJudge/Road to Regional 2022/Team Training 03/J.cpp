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

int nearestPowerTwo(int n){
    int r = 1;
    while(r < n) r<<=1;
    return r;
}

lli powerMod(lli a, lli b, lli mod){
	lli res = 1;
	b %= mod-1;
	if(b < 0) b += mod-1;
	while(b){
		if(b & 1) res = (res * a) % mod;
		b >>= 1;
		a = (a * a) % mod;
	}
	return res;
}

template<int p, int g, typename T>
void ntt(vector<T> & A, bool inv){ 
	int n = SZ(A);
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(A[i], A[j]);
	}

	vector<lli> wp(n>>1, 1);

	for(int k = 1; k < n; k <<= 1){
		lli wk = powerMod(g, (inv?-1:1) * (p - 1) / (k<<1), p);
		for(int j = 1; j < k; ++j)
			wp[j] = (wp[j - 1] * wk) % p;

		for(int i = 0; i < n; i += k << 1){
			for(int j = 0; j < k; ++j){
				int u = A[i + j], v = (A[i+j+k] * wp[j]) % p;
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
vector<T> multiply(vector<T> A, vector<T> B){ //O(n logn) it uses NTT
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


void test(int n, string s){
    vector< int > non_valid_shifts(2*n+1, false);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(s[i] != s[j] && s[i] != '?' && s[j] != '?') {
                non_valid_shifts[n + j - i]++;
            } 
        }
    }

    for(int i = 1; i <= 2*n; i++) cout << (non_valid_shifts[i]>0) << " ";
    cout << endl;

    for(int d = 1; d <= n; d++) {
        bool valid = true;
        for(int k = 1; k*d < n; k++) {
            if(non_valid_shifts[k*d]) {
                valid = false;
            }
        }
        if(valid) {
            cout << "Esta madre no incumple " << d << endl;
        }
    }
}


void solve(){
    int n; cin>>n;
    string s; cin>>s;


    //test(n, s);

    vector<int> Vs(n), Ks(n), Ws(n);

    for(int i = 0; i < n; i++) {
        Vs[i] = (s[i] == 'V');
    }

    for(int i = 0; i < n; i++) {
        Ks[i] = (s[i] == 'K');
    }

    reverse(all(Vs));

    auto DIFF = multiply(Vs, Ks);

    vector< int > non_valid_shifts(n+1);

    for(int d = 0; d < SZ(DIFF); d++) {
        non_valid_shifts[abs(d - n + 1)] |= (DIFF[d] != 0);
    }

    vector<int> ans;
    for(int d = 1; d <= n; d++) {
        bool valid = true;
        for(int k = 1; k*d <= n; k++) {
            if(non_valid_shifts[k*d]) {
                valid = false;
            }
        }
        if(valid) {
            ans.push_back(d);
        }
    }

    cout << SZ(ans) << endl;
    for(auto x: ans) cout << x << " ";
    cout << endl;    
}


int main () {
	fastIO();
	
    int t; cin>>t;

    while(t--) solve();


	return 0;
}

