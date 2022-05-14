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
    Matrix operator*(const Matrix &B) const{

        assert(cols == B.rows);
        Matrix<T> C(rows, B.cols);
 
        for(int i = 0; i<rows; i++)
            for(int j = 0; j<B.cols; j++)
                for(int k = 0; k<cols; k++)
                    C[i][j] += (A[i][k]*B[k][j]);

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

};


int main () {
	fastIO();
  lli n, m; cin>>n>>m;
  Matrix<ld> A(n,n);
  for(int i = 0; i<n; i++)
  {
    for(int j = 0; j<n; j++)
    {
      cin>>A[i][j];
    }
  }

  A = A^m;

  for(int i = 0; i<n; i++)
  {
    cout << A[0][i] << endl;
  } 

	return 0;
}