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


// int n;
// int k;


// map< pair<lli,lli>, lli > dp;

// lli f(int idx, int last_number) {
//     if(idx == n+1) {
//         return 1;
//     }

//     if(dp.count({idx, last_number})) return dp[{idx, last_number}];

//     int ans_t = 0;    
//     for(int d = 1; d <= k; d++) {
//         if(gcd(last_number, d) == 1){
//             ans_t += f(idx+1, d);
//         }
//     }
//     return dp[{idx, last_number}] = ans_t;
// }


const lli MOD = 1e9+7;


template <typename T>
struct Matrix{
    vector< vector< T > > A;
    lli rows, cols;

    //* ///////// INIT & STATICS //////////////////////
 
    Matrix(): rows(0), cols(0) {}
 
    Matrix(lli n, lli m): rows(n), cols(m) // Matrix of n rows and m cols
    {
        A.assign(n, vector<T>(m));
    }

    vector<T> &operator[] (int i){ return A[i]; }
    const vector<T> &operator[] (int i) const{ return A[i]; } // To get access without dot

    static Matrix Identity(lli n) // Identity Matrix<T>::Identity(rows)
    {
        Matrix<T> I(n,n);
        for(int i = 0; i<n; i++) I[i][i] = 1;
        return I;
    }


    Matrix operator*(lli k) const{
        Matrix<T> C(rows, cols);
        for(int i = 0; i<rows; i++)
            for(int j = 0; j<cols; j++)
                C[i][j] = k*A[i][j];
        return C;
    }
    
    Matrix operator*(const Matrix &B) const{

        assert(cols == B.rows);
        Matrix<T> C(rows, B.cols);
 
        for(int i = 0; i<rows; i++)
            for(int j = 0; j<B.cols; j++)
                for(int k = 0; k<cols; k++) {
                    C[i][j] += (A[i][k]*B[k][j]) % MOD;
                    if(C[i][j] >= MOD) C[i][j] -= MOD;
                }
                    

        return C;           
    }
 
    Matrix operator^(lli e) const{
        Matrix<T> res = Matrix<T>::Identity(rows);
        Matrix<T> aux = *this;
        while(e)
        {
            if(e&1) res = res*aux;
            e >>= 1;
            aux = aux*aux;
        }
        return res;
    }
};


int main () {
	//fastIO();

    lli k, n; cin>>k>>n;
    Matrix<lli> M(k+1, k+1);

    for(int i = 1; i <= k; i++) {
        for(int j = 1; j <= k; j++) {
            if(__gcd(i, j) == 1) {
                M[i][j] = 1;
            }
        }
    }

    M = M^(n+1);
    cout << M[1][1] << endl;


	return 0;
}

