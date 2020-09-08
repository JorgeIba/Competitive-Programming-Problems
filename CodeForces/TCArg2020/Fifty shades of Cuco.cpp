#include <bits/stdc++.h>
#include<complex>
#include<cmath>
#define lli long long int
#define ld double
#define endl "\n"
#define forn(i, in, fin) for(lli i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;
 
int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}
 
lli powerMod(lli b, lli e, lli m){
	lli ans = 1;
	e %= m-1;
	if(e < 0) e += m-1;
	while(e){
		if(e & 1) ans = ans * b % m;
		e >>= 1;
		b = b * b % m;
	}
	return ans;
}
 
template<int p, int g>
void ntt(vector<int> & X, int inv){
	int n = X.size();
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	vector<lli> wp(n>>1, 1);
	for(int k = 1; k < n; k <<= 1){
		lli wk = powerMod(g, inv * (p - 1) / (k<<1), p);
		for(int j = 1; j < k; ++j)
			wp[j] = wp[j - 1] * wk % p;
		for(int i = 0; i < n; i += k << 1){
			for(int j = 0; j < k; ++j){
				int u = X[i + j], v = X[i + j + k] * wp[j] % p;
				X[i + j] = u + v < p ? u + v : u + v - p;
				X[i + j + k] = u - v < 0 ? u - v + p : u - v;
			}
		}
	}
	if(inv == -1){
		lli nrev = powerMod(n, p - 2, p);
		for(int i = 0; i < n; ++i)
			X[i] = X[i] * nrev % p;
	}
}
 
template<int p, int g>
vector<int> mult(vector<int> A, vector<int> B){
	int sz = A.size() + B.size() - 1;
	int size = nearestPowerOfTwo(sz);
	A.resize(size), B.resize(size);
	ntt<p, g>(A, 1), ntt<p, g>(B, 1);
	for(int i = 0; i < size; i++)
		A[i] = (lli)A[i] * B[i] % p;
	ntt<p, g>(A, -1);
	A.resize(sz);
	return A;
}

int main(){
    fastIO();
    lli n, m; cin>>n>>m;
    string s, t; cin>>s>>t;
    vector< int > as(n), bs(n);
    vector< int > at(n), bt(n);

    for(int i = 0; i<n; i++)
    {
        at[i] = bt[i] = 0;
        if(s[i] == 'a')
        {
            as[i] = 1;
            bs[i] = 0;
        } 
        else 
        {
            as[i] = 0;
            bs[i] = 1;
        }
    }
    for(int i = 0; i<m; i++)
    {
        if(t[i] == 'a') 
        {
            at[i] = 1;
            bt[i] = 0;
        }
        else
        {
            at[i] = 0;
            bt[i] = 1;
        } 
    }
    reverse(all(at));
    reverse(all(bt));
    auto Ca = mult<998244353, 3> (as, at);
    auto Cb = mult<998244353, 3> (bs, bt);

    vector< vector< int > > ans(m+1);
    lli cont = 1;
    for(lli i = n-1; i<n+n-m; i++)
    {
        lli a = Ca[i];
        lli b = Cb[i];
        ans[(m-(a+b))].push_back(cont++);
    }
    for(lli i = 0; i<m+1; i++)
    {
        cout << i << ": ";
        for(auto x: ans[i])
        {
            cout << x << " ";
        }
        cout << endl;
    }
	
	return 0;
}