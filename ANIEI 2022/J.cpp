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


const int MOD = 700666007;

#define Matrix vector<vector<int>>

vector<vector<int>> M(3, vector<int>(3));
vector<vector<int>> A(3, vector<int>(3));


const int maxPow = 49;
vector< Matrix > pows(maxPow);


Matrix mult(const Matrix &A, const Matrix &B){

    Matrix C(3, vector<int>(3));

    for(int i = 0; i<3; i++)
        for(int j = 0; j< 3; j++)
            for(int k = 0; k<3; k++)
                {
                    (C[i][j] += (1LL*A[i][k]*B[k][j]) % MOD);
                    if(C[i][j] >= MOD) C[i][j] -= MOD;
                }

    return C;           
}
 
Matrix powM(Matrix aux, lli e){
    Matrix res(3, vector<int>(3));
    for(int i = 0; i < 3; i++) res[i][i] = 1;

    lli curr = 0;
    while(e)
    {
        if(e&1) res = mult(res, aux);
        e>>=1;
        curr++;
        if(e) aux = pows[curr];
    }
    return res;
}




void prec(){
    M[0][0] = 2;
    M[0][1] = 1;
    M[0][2] = 0;

    M[1][0] = 0;
    M[1][1] = 0;
    M[1][2] = 1;

    M[2][0] = 0;
    M[2][1] = 1;
    M[2][2] = 1;

    A[0][0] = 1;
    A[1][0] = 0;
    A[2][0] = 1;


    pows[0] = M;
    for(int i = 1; i < maxPow; i++) {
        pows[i] = mult(pows[i-1], pows[i-1]);
    }

}

inline void modula(lli & n, lli mod){
	while(n >= mod) n -= mod;
}

lli fibo(lli n, lli mod){
	array<lli, 2> F = {1, 0};
	lli p = 1;
	for(lli v = n; v >>= 1; p <<= 1);
	array<lli, 4> C;
	do{
		int d = (n & p) != 0;
		C[0] = C[3] = 0;
		C[d] = F[0] * F[0] % mod;
		C[d+1] = (F[0] * F[1] << 1) % mod;
		C[d+2] = F[1] * F[1] % mod;
		F[0] = C[0] + C[2] + C[3];
		F[1] = C[1] + C[2] + (C[3] << 1);
		modula(F[0], mod), modula(F[1], mod);
	}while(p >>= 1);
	return F[1];
}

lli powerMod(lli a, lli b, lli mod) {
    lli res = 1;
    while(b) {
        if(b&1) res = res * a % mod;
        b >>= 1;
        a = a*a % mod;
    }
    return res;
}

lli count_n(lli n) {
    /*
    auto ANS = mult(powM(M, n+1), A);
    return (ANS[0][0] - fibo(n+2, MOD) + MOD) % MOD;
    */

    return (powerMod(2, n, MOD) - fibo(n+2, MOD) + MOD) % MOD;
}


int main () {
	fastIO();

    time_t start = clock();

    prec();

    
    for(int t = 1; t <= 1e4; t++) {
        lli a=1e14, b=1e14;
        lli ans = (count_n(b+1) - count_n(a) + MOD) % MOD;
        // cout << ans << " ";
    }
    
    cout << (double)(clock() - start) /CLOCKS_PER_SEC << endl;

	return 0;
}

