#include <bits/stdc++.h>

#define lli long long int
#define ld double
#define endl "\n"
#define forn(i, in, fin) for(lli i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

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

string s, t; // C G T A
vector< int > Cs, Ct;
vector< int > Gs, Gt;
vector< int > Ts, Tt;
vector< int > As, At;

void getCoefficients(char letra)
{
    for(int i = 0; i<SZ(s); i++)
    {
        if(s[i] == letra) 
        {
            if(letra == 'C') Cs[i] = 1;
            else if(letra == 'G') Gs[i] = 1;
            else if(letra == 'T') Ts[i] = 1;
            else As[i] = 1;
        }
    }

    for(int i = 0; i<SZ(t); i++)
    {
        if(t[i] == letra)
            {
                if(letra == 'C') Ct[i] = 1;
                else if(letra == 'G') Gt[i] = 1;
                else if(letra == 'T') Tt[i] = 1;
                else At[i] = 1;
        }
    }  
}

void prep(lli N)
{
    Cs.clear(); Ct.clear();
    Gs.clear(); Gt.clear();
    Ts.clear(); Tt.clear();
    As.clear(); At.clear();
    Cs.resize(N); Ct.resize(N);
    Gs.resize(N); Gt.resize(N);
    Ts.resize(N); Tt.resize(N);
    As.resize(N); At.resize(N);
    getCoefficients('C');
    getCoefficients('G');
    getCoefficients('T');
    getCoefficients('A');
    reverse(all(Ct));
    reverse(all(Gt));
    reverse(all(Tt));
    reverse(all(At));
}

void solve(string &s, string &t){
    bool swapee = false;
    if(SZ(s) < SZ(t)) swap(s, t), swapee = true;
    lli n = s.length(), m = t.length();
    lli N = max(n, m);
    prep(N);

    auto MatchingC = mult<998244353, 3> (Cs, Ct);
    auto MatchingG = mult<998244353, 3> (Gs, Gt);
    auto MatchingT = mult<998244353, 3> (Ts, Tt);
    auto MatchingA = mult<998244353, 3> (As, At);

    lli maximumMatch = 0, idx=0;
    for(int i = 0; i<SZ(MatchingA); i++)
    {
        lli suma = (MatchingC[i] + MatchingG[i] + MatchingT[i] + MatchingA[i]);
        //cerr << suma << " " << i-n+1 << endl;
        assert(suma >= 0);
        if(swapee)
        {
            if(suma > maximumMatch) maximumMatch = suma, idx = i-n+1;
        }
        else
        {
            if(suma >= maximumMatch) maximumMatch = suma, idx = i-n+1;
        }    
    }
    

    cout << maximumMatch << endl;
    if(maximumMatch == 0)
    {
        cout << "No matches";
    }
    else
    {
        const lli maxN = 3*(1e5) + 10;
        char ans[2*maxN];
        for(int i = 0; i<2*maxN; i++) ans[i] = 'X';
        if(idx < 0)//pa la izquierda
        {
            idx = abs(idx);
            for(int i = 0; i<m; i++)
            {
                ans[i] = t[i];
            }
            for(int i = idx; i<idx+n; i++)
            {
                if(ans[i] != 'X')
                {
                    if(ans[i] != s[i-idx]) ans[i] = 'X';
                }
                else
                {
                    ans[i] = s[i-idx];
                }
            }
            // Imprimir
            for(int i = 0; i<max(m,idx+n); i++) cout << ans[i];
        }
        else //pa la derecha
        {
            for(int i = 0; i<n; i++)
                ans[i] = s[i];
            for(int i = idx; i<m+idx; i++)
            {
                if(ans[i] != 'X')
                {
                    if(ans[i] != t[i-idx]) ans[i] = 'X';
                }
                else
                {
                    ans[i] = t[i-idx];
                }
                    
            }
            for(int i = 0; i<max(n, idx+m); i++) cout << ans[i];
        }
    }    
    cout << endl << endl;
    
    return;
}

int main()
{
    //fastIO();
    while(cin>>s>>t)
    {
        solve(s, t);
    }
}