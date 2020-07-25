#include <bits/stdc++.h>
#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

template <typename T>
struct Matrix{
    vector< vector< T > > A;
    lli rows, cols;

    //* ///////// INIT & STATICS //////////////////////
 
    Matrix(): rows(0), cols(0) {}
 
    Matrix(lli n, lli m, T value = 0): rows(n), cols(m)
    {
        A.assign(n, vector<T>(m, value));
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

    Matrix operator*(const Matrix &B) const{

        assert(cols == B.rows);
        Matrix<T> C(rows, B.cols);
 
        for(int i = 0; i<rows; i++)
            for(int j = 0; j<B.cols; j++)
                for(int k = 0; k<cols; k++)
                    C[i][j] = (C[i][j] + (A[i][k] * B[k][j]));
        return C;           
    }
 
    Matrix operator^(lli e) const{
        Matrix<T> res = Matrix<T>::Identity(rows);
        Matrix<T> I = Matrix<T>::Identity(rows);
        Matrix<T> aux = *this;
        while(e)
        {
            if(e&1)
            {
                res = res*aux;
            }  
            e>>=1;
            aux = aux*aux;
        }
        return res;
    }
};

bool isValid(lli i, lli j)
{
    if(i >= 0 && j >= 0 && i < 8 && j < 8) return true;
    return false;
}

const lli lng = 64 + 8;
int main()
{
    //fastIO();
    vector< pair<lli,lli> > diff = {{2, 1}, {2, -1}, {-2, 1}, {-2,-1}, {1, 2}, {-1, 2}, {1, -2}, {-1, -2} };
    Matrix<unsigned int> T(2*lng, 2*lng);

    for(int i = 0; i<8; i++)
    {
        for(int j = 0; j<8; j++)
        {
            for(auto p: diff)
            {
                lli di = p.first, dj = p.second;
                if( isValid(i + di, j + dj) )
                {
                    T[2*(  i*8 + j ) ][ 2* ((i+di)*8 + (j+dj)) ] = 1;
                }
            }
            T[2*(  i*8 + j ) ][2*(  i*8 + j ) + 1 ] = 1;
            T[2*(  i*8 + j ) + 1 ][2*(  i*8 + j ) + 1 ] = 1;
        }
    }

    lli n; cin>>n;

    T = T^n;

    unsigned int suma2 = 0;
    for(int i = 0; i<2*lng; i++)
    {
        suma2 += T[0][i];
        suma2 += T[1][i];
    }

    cout << (suma2 - 1) << endl;

    


    return 0;
}