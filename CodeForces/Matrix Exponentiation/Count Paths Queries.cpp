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
        Matrix<T> aux = pot[0];
        lli curr = 0;
        while(e)
        {
            if(e&1) res = res*aux;
            e>>=1;
            curr++;
            if(e) aux = pot[curr];
        }
        return res;
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

inline int read()
{
	int x=0,f=1,c=getchar();
	while(c<48) c=='-'&&(f=-1),c=getchar();
	while(c>47) x=x*10+c-'0',c=getchar();
	return x*f;
}
 
int main()
{
    fastIO();
    lli n=read(), m=read(), q=read();
    Matrix<lli> T(n,n);
    for(int i = 0; i<m; i++)
    {
        lli u = read(), v = read(); u--, v--;
        T[u][v] = 1;
    }
    
    Matrix<lli> A = T;
    A.pot[0] = T;
    for(int i = 1; i<30; i++)
    {
        A.pot[i] = A.pot[i-1] * A.pot[i-1];
    }
    
    vector< tuple<int, int, int, int> > queries(q);
    for(int i = 0; i<q; i++)
    {
        lli s=read(), t=read(), k=read(); s--, t--;
        queries[i] = {k, s, t, i};
        //Query Q(s,t,k,i);
        //queries[i] = Q;
    }

    //sort(all(queries), cmp);
    sort(all(queries));
    vector< lli > ans(q);
    lli curr = 1;
    for(int i = 0; i<q; i++)
    {
        //Query C = queries[i];
        int diff = get<0>(queries[i]) - curr;
        if(diff > 0)
        {
            T = T * (A^diff);
            curr = get<0>(queries[i]);
        }
        ans[get<3>(queries[i])] = T[get<1>(queries[i])][get<2>(queries[i])];
    }
    for(int i = 0; i<q; i++)
    {
        cout << ans[i] << endl;
    }
    

    return 0;
}