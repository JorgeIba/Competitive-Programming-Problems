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


const int maxK = (1<<17);


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

const int p = 1e9+7;

//Fast Walsh-Hadamard transform, works with any modulo p
//op: 0(OR), 1(AND), 2(XOR), A.size() must be power of 2
void fwt(vector<lli> & A, int op, int inv){
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

int main () {
	fastIO();

    vector<lli> fib(maxK); fib[1] = 1;
    for(int i = 2; i<maxK; i++) fib[i] = (fib[i-1] + fib[i-2])%p;


    lli n; cin>>n;
    vector<lli> a(maxK), B(maxK), C(maxK);
    for(int i = 0; i<n; i++)
    {
        lli x; cin>>x;
        a[x]++; B[x]++; C[x]++;
    }

    VLL A(maxK);
    for(int i = 0; i<maxK; i++) //Some s_a | s_b
    {
        for(int j = i; j>0; j = (j-1)&i) //Submask of some s_a|s_b
            A[i] = (A[i] + (a[j]*a[j^i]%p))%p;         // j and j^i are disjoints, then j & (j^i) == 0 and j | (j^i) = i
        A[i] = (A[i] + (a[i]*a[0]%p))%p;
    }

    fwt(C, 2, 1);
    for(auto &x: C) x = (lli)x*x%p; //every s_d ^ s_e
    fwt(C, 2, -1);


    for(int i = 0; i<maxK; i++)
    {
        A[i] = A[i]*fib[i]%p;
        B[i] = B[i]*fib[i]%p;
        C[i] = C[i]*fib[i]%p;
    }

    fwt(A, 1, 1);
    fwt(B, 1, 1);
    fwt(C, 1, 1);

    for(int i = 0; i<maxK; i++)
    {
        A[i] = A[i]*B[i]%p*C[i]%p;
    }
    fwt(A, 1, -1);

    lli ans = 0;
    for(int i = 0; i<17; i++)
    {
        ans = (ans + A[(1<<i)])%p;
    }
    cout << ans << endl;





	return 0;
}