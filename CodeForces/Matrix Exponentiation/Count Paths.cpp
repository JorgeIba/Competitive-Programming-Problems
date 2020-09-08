#include <bits/stdc++.h>
#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli MOD = 1000000007;

template <typename T>
struct Matrix{
    vector< vector< T > > A;
    lli rows, cols;

    //* ///////// INIT & STATICS //////////////////////
 
    Matrix(): rows(0), cols(0) {}
 
    Matrix(lli n, lli m): rows(n), cols(m)
    {
        A.assign(n, vector<T>(m));
    }
 
    Matrix(lli n): rows(n), cols(n) 
    {
        A.assign(n, vector<T>(n, 0));
        for(int i = 0; i<rows; i++)
        {
            A[i][i] = 1;
        }
    }

    vector<T> &operator[] (int i){ return A[i]; }
    const vector<T> &operator[] (int i) const{ return A[i]; }

    static Matrix Identity(lli n)
    {
        Matrix<T> I(n,n);
        for(int i = 0; i<n; i++) I[i][i] = 1;
        return I;
    }

    //* /////////////////// Operators ////////////////////////

    Matrix operator+(lli k) const{
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
                for(int k = 0; k<cols; k++)
                    C[i][j] = (C[i][j] + ((A[i][k]*B[k][j])%MOD) )%MOD;

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

    Matrix operator+(const Matrix &B) const{
        assert(rows == B.rows && cols == B.cols);
        Matrix<T> C(rows, cols);
        for(int i = 0; i<rows; i++)
            for(int j = 0; j<cols; j++)
                C[i][j] = A[i][j] + B[i][j];
        return C;
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
    }
};



int main()
{
    fastIO();
    lli n, m, k; cin>>n>>m>>k;
    Matrix<lli> T(n,n);
    for(int i = 0; i<m; i++)
    {
        lli u, v; cin >> u >> v; u--, v--;
        T[u][v] = 1;
    }

    T = T^k;

    lli sum = 0;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            sum += T[i][j];
        }
    }

    cout << (sum%MOD) << endl;

    //T.printMatrix();


    return 0;
}