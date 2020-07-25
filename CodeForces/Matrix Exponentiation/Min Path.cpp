#include <bits/stdc++.h>
#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli INF = numeric_limits<lli>::max();

template <typename T>
struct Matrix{
    vector< vector< T > > A;
    lli rows, cols;

    //* ///////// INIT & STATICS //////////////////////
 
    Matrix(): rows(0), cols(0) {}
 
    Matrix(lli n, lli m): rows(n), cols(m)
    {
        A.assign(n, vector<T>(m, INF));
    }

    vector<T> &operator[] (int i){ return A[i]; }
    const vector<T> &operator[] (int i) const{ return A[i]; }

    static Matrix Identity(lli n)
    {
        Matrix<T> I(n,n);
        for(int i = 0; i<n; i++) I[i][i] = 0;
        return I;
    }

    //* /////////////////// Operators ////////////////////////
    Matrix operator*(const Matrix &B) const{

        assert(cols == B.rows);
        Matrix<T> C(rows, B.cols);
 
        for(int i = 0; i<rows; i++)
            for(int j = 0; j<B.cols; j++)
                for(int k = 0; k<cols; k++)
                {
                    if(A[i][k] == INF || B[k][j] == INF) continue;
                    C[i][j] = min(C[i][j], (A[i][k] + B[k][j]) );
                    assert(abs(C[i][j]) < INF);
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
    }
};


int main()
{
    fastIO();
    lli n, m, k; cin>>n>>m>>k;
    Matrix<lli> T(n,n);

    for(int i = 0; i<m; i++)
    {
        lli u, v, w; cin>>u>>v>>w; u--, v--;
        T[u][v] = w;
    }

    //T.printMatrix();

    T = T^(k);

    //T.printMatrix();

    lli res = INF;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            res = min(res, T[i][j]);
        }
    }
    
    if(res == INF)
    {
        cout << "IMPOSSIBLE\n";
    }
    else
    {
        cout << res << endl;
    }

    return 0;
}