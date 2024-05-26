#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;
vector<lli> cannot;
const lli mod = 1e9+7;
const lli MOD = 1e9+7;
int n, m;

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

    //* /////////////////// Operators ////////////////////////

    Matrix operator*(lli k) const{
        Matrix<T> C(rows, cols);
        for(int i = 0; i<rows; i++)
            for(int j = 0; j<cols; j++)
                C[i][j] = k*A[i][j];
        return C;
    }
    
    Matrix operator*(const Matrix &B) const{
        Matrix<T> C(rows, B.cols);
 
        for(int i = 0; i<rows; i++)
            for(int j = 0; j<B.cols; j++)
                for(int k = 0; k<cols; k++) {
                    C[i][j] += (A[i][k]*B[k][j]) % mod;
										if(C[i][j] >= mod) C[i][j] -= mod;
								}

        return C;           
    }
 
    Matrix operator^(lli e) const{
        Matrix<T> res = Matrix<T>::Identity(rows);
        Matrix<T> aux = *this;
        while(e)
        {
            if(e&1) res = res*aux;
            e>>=1;
            aux = aux*aux;
        }
        return res;
    }

    //* //////////////////////////////////////////////
    void printMatrix()
    {
        for(int i = 0; i<rows; i++)
        {
            cout<<"|";
            for(int j = 0; j<cols; j++)
            {
                cout<<A[i][j]<< (j!=cols-1? " ": "");
            }
            cout<<"|\n";
        }
        cout << endl;
    } 
};
vector<Matrix<lli>> pot;
void precal() {
    pot.push_back(Matrix<lli>::Identity(2));
    Matrix<lli> mat(2,2);
    mat[0][0] = 1;
	mat[0][1] = 1;
	mat[1][0] = 1;
	mat[1][1] = 0;
    pot.push_back(mat);
    int i = 2;
    for(lli x = 2; x <= 1e9; x *= 2) {
        pot.push_back(pot[i-1]*pot[i-1]);
        i++;
    }
}
lli fibo(lli k) {
    if(k <= 0) return 0;
    int i = 1;
    Matrix<lli> aux = Matrix<lli>::Identity(2);
    while(k) {
        if(k&1) aux = aux * pot[i];
        i++;
        k >>= 1;
    }
    return aux[0][1];
}


int main() {
	fastIO();
    precal();
	cin >> n >> m;
    forn(i,m) {
        lli x;
        cin >> x;
        if(x > n) continue;
        cannot.push_back(x);
    }
	sort(all(cannot));
    
    cannot.erase( unique( all(cannot) ), cannot.end() );
    vector<lli> calc;
    if(cannot.size())
	    calc.push_back(cannot[0]);
	for(int i = 1; i < SZ(cannot); i++) {
		calc.push_back(cannot[i] - cannot[i-1] - 1);
	}
    if(cannot.size()) 
	    calc.push_back(n - cannot[cannot.size() - 1]);

	lli ans = 1;
	for(lli x : calc) {
        ans = ans * fibo(x) % MOD;
	}
    if(cannot.size() == 0) {
        ans = fibo(n+1);
    }
	cout << ans << '\n';
	return 0;
    
}