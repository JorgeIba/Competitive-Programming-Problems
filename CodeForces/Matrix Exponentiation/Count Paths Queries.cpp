#include <bits/stdc++.h>
#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli MOD = 1e9 + 7;

template <typename T>
struct Matrix{
    vector< vector< T > > A;
    vector< Matrix<T> > pot;
    lli rows, cols;

    //* ///////// INIT & STATICS //////////////////////
 
    Matrix(): rows(0), cols(0) {}
 
    Matrix(lli n, lli m): rows(n), cols(m)
    {
        A.assign(n, vector<T>(m));
        pot.resize(30);
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

        //assert(cols == B.rows);
        Matrix<T> C(rows, B.cols);
 
        for(int i = 0; i<rows; i++)
            for(int j = 0; j<B.cols; j++)
                for(int k = 0; k<cols; k++)
                    C[i][j] = (C[i][j] + (A[i][k]*B[k][j]))%MOD;

        return C;           
    }
 
    Matrix operator^(lli e) const{
        Matrix<T> res = Matrix<T>::Identity(rows);
        lli curr = 0;
        // bool flag = true;
        
        while(e)
        {
            if(e&1){
                /*
                if(flag) {
                    cout << "PRIMERO: ";
                    pot[curr].printMatrix();
                    flag = false;
                }
                */
                res = res*pot[curr];
            } 
            e>>=1;
            curr++;
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

struct Query
{
    lli s, t, k, idx;
    Query():s(0), t(0), k(0), idx(0) {}
    Query(lli s, lli t, lli k, lli idx): s(s), t(t), k(k), idx(idx) {}
};

bool cmp(Query a, Query b)
{
    return a.k < b.k;
}

//vector< Matrix<lli> > pot(31);

int main()
{
    fastIO();
    lli n, m, q; cin>>n>>m>>q;
    Matrix<lli> T(n,n);
    for(int i = 0; i<m; i++)
    {
        lli u, v; cin>>u>>v; u--, v--;
        T[u][v] = 1;
    }
    
    Matrix<lli> A = T;
    A.pot[0] = T;
    for(int i = 1; i<30; i++)
    {
        A.pot[i] = A.pot[i-1] * A.pot[i-1];
    }
    
    for(int i = 0; i < q; i++) { 
        lli s, t, k; cin>>s>>t>>k; s--, t--;

        // auto S = A^k;

        lli curr = 0;
        for(int j = 0; j < 30; j++)
            if((1<<j) & k){
                curr = j;
                break;
            }
    
        Matrix<lli> IN = A.pot[curr];
        Matrix<lli> Q(1, n);

        for(int j = 0; j < n; j++) {
            Q[0][j] = IN[s][j];
        }

        k >>= (++curr);

        while(k) {
            if(k & 1) Q = Q * A.pot[curr];
            k >>= 1;
            curr++;
        }

        cout << Q[0][t] << endl;
    }




    return 0;
}