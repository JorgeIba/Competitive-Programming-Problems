#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


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

const int p = 998244353;

//Fast Walsh-Hadamard transform, works with any modulo p
//op: 0(OR), 1(AND), 2(XOR), A.size() must be power of 2
void fwt(vector<int> & A, int op, int inv){
	int n = A.size();
	for(int k = 1; k < n; k <<= 1)
		for(int i = 0; i < n; i += k << 1)
			for(int j = 0; j < k; ++j){
				int u = A[i + j], v = A[i + j + k];
				int sum = u + v < p ? u + v : u + v - p;
				int rest = u - v < 0 ? u - v + p : u - v;
				if(inv == -1){
					if(op == 0)
						A[i + j + k] = rest ? p - rest : 0;
					else if(op == 1)
						A[i + j] = rest;
					else if(op == 2)
						A[i + j] = sum, A[i + j + k] = rest;
				}else{
					if(op == 0)
						A[i + j + k] = sum;
					else if(op == 1)
						A[i + j] = sum;
					else if(op == 2)
						A[i + j] = sum, A[i + j + k] = rest;
				}
			}
	if(inv == -1 && op == 2){
		lli nrev = powerMod(n, p-2, p);
		for(int i = 0; i < n; ++i)
			A[i] = A[i] * nrev % p;
	}
}

const int maxK = (1<<17);

void convolution(vector<int> &A, vector<int> B){
	int sz = A.size() + B.size() - 1;
	int size = nearestPowerOfTwo(sz);
	A.resize(size), B.resize(size);
	fwt(A, 2, 1), fwt(B, 2, 1);
	for(int i = 0; i < size; i++)
		A[i] = (lli)A[i] * B[i] % p;
	fwt(A, 2, -1);
	A.resize(min(maxK,sz));
}

vector<int> powConv(vector<int> A, int b)
{
    VI RES(maxK);
    RES[0] = 1;

    VI P(maxK);
    for(int i = 0; i<min(SZ(A), SZ(P)); i++) P[i] = A[i];

    fwt(RES, 2, 1);
    fwt(P, 2, 1);
    
    while(b)
    {
        if(b&1)
        {
           for(int i = 0; i<maxK; i++) RES[i] = (lli)RES[i]*P[i] % p;
        }
        b>>=1;
        for(int i = 0; i<maxK; i++) P[i] = (lli)P[i]*P[i] % p;
    }
    fwt(RES, 2, -1);
    return RES;
}




int main()
{
    fastIO();
    lli m, k; cin>>m>>k;
    
    vector< int > pilas(k), P(maxK);
    for(auto &x: pilas)
    {
        cin>>x;
        P[x]++;
    }

    P = powConv(P, m);
    lli ans = 0;
    for(int i = 1; i<SZ(P); i++)
    {
        ans += P[i];
        if(ans >= p) ans -= p;
    }
    lli Q = powerMod(k, m, p);
    cout << ans*powerMod(Q, p-2, p)%p << endl;

    return 0;
}