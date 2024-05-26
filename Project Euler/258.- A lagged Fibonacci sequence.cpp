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


const lli MOD = 20092010;


vector<lli> powerMod(const vector<lli> &A, const vector<lli> &B, const vector<lli> &M) {
    auto [n, m] = tuple<lli,lli> { SZ(A), SZ(B) };
    vector<lli> C(n + m - 1);

    lli degree = SZ(M);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            (C[i+j] += A[i] * B[j]) %= MOD;
        }
    }

    for(int i = SZ(C)-1; i >= degree; i--){
        for(int j = 0; j < SZ(M); j++) {
            (C[i - degree + j] += M[j] * C[i]) %= MOD;
        }
    }

    C.resize(min(SZ(C), SZ(M)));
    return C;
}

vector<lli> binPowMod(vector<lli> A, lli k, const vector<lli> &M) {
    vector<lli> ANS = {1};
    while(k)
    {
        if(k&1){
            ANS = powerMod(ANS, A, M);
        }
        k >>= 1;
        A = powerMod(A, A, M);
    }
    return ANS;
}


lli KthTermLinearRecurrence(const vector<lli> &initial, const vector<lli> &constants, lli k) {
    lli n = SZ(initial);
    if(k < n) return initial[k];

    vector<lli> A = {0, 1};
    auto modu = binPowMod(A, k, constants);


    lli ans = 0;

    for(int i = 0; i < SZ(modu); i++) {
        (ans += initial[i] * modu[i]) %= MOD;
    }

    return ans;
}


int main () {
	//fastIO();
    
    lli k = 1e18;

    vector<lli> initial(2000, 1), constants(2000);
    constants[0] = constants[1] = 1;

    cout << KthTermLinearRecurrence(initial, constants, k) << endl;

	return 0;
}

