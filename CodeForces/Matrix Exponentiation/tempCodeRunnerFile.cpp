#include <bits/stdc++.h>
#define lli long unsigned int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli MOD = 1e9 + 7;

const lli maxN = 205;
lli T[maxN][maxN], A[maxN][maxN], I[maxN][maxN], C[maxN][maxN], B[maxN][maxN]; 
int n, m, q; 

void mult(lli index)
{
    if(index == 1) // Multiplicar I =  I*A
    {
        for(int i = 0; i<n; i++)
            for(int j = 0; j<n; j++)
            {
                C[i][j] = 0;
                for(int k = 0; k<n; k++)
                {
                    lli poss = (I[i][k] * A[k][j])%MOD;
                    C[i][j] = (C[i][j] + poss);
                    if(C[i][j] >= MOD) C[i][j] -= MOD;
                    //C[i][j] += I[i][k]*A[k][j];
                }
            }
        forn(i,0,n) forn(j,0, n) I[i][j] = C[i][j];
    }
    if(index == 2) // Multiplicar A = A*A
    {
        for(int i = 0; i<n; i++)
            for(int j = 0; j<n; j++)
            {
                C[i][j] = 0;
                for(int k = 0; k<n; k++)
                {
                    lli poss = (A[i][k] * A[k][j])%MOD;
                    C[i][j] = (C[i][j] + poss);
                    if(C[i][j] >= MOD) C[i][j] -= MOD;
                    //C[i][j] += A[i][k]*A[k][j];
                }
            }
        forn(i,0,n) forn(j,0,n) A[i][j] = C[i][j];   
    }

    if(index == 3) // Multiplicar T = T * A^exp;
    {
        for(int i = 0; i<n; i++)
            for(int j = 0; j<n; j++)
            {
                C[i][j] = 0;
                for(int k = 0; k<n; k++)
                {
                    lli poss = (T[i][k] * A[k][j])%MOD;
                    C[i][j] = (C[i][j] + poss);
                    if(C[i][j] >= MOD) C[i][j] -= MOD;
                }
            }
        forn(i,0,n) forn(j,0, n) T[i][j] = C[i][j];
    }
}


void matExp(lli e)
{   
    while(e)
    {
        if(e&1) //I = I*A;
        {
            mult(1);
        } 
        //A = A*A;
        e >>= 1;
        mult(2);
    }
}

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

void expB(lli diff)
{
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            A[i][j] = B[i][j];
            if(i==j) I[i][j] = 1;
            else I[i][j] = 0;
        }
    }

    matExp(diff);

    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            A[i][j] = I[i][j];
        }
    }
    
}


int main()
{
    //fastIO();
    int q; scanf("%d%d%d", &n, &m, &q);
    memset(T, 0, sizeof(T));
    memset(B, 0, sizeof(B));
    for(int i = 0; i<m; i++)
    {
        int u, v;  scanf("%d%d", &u, &v);
        //lli u, v; cin>>u>>v;
        u--, v--;
        B[u][v] = 1;
        T[u][v] = 1;
    }

    
    vector< Query > queries(q);
    for(int i = 0; i<q; i++)
    {
        int s, t, k;
        scanf("%d%d%d", &s, &t, &k);
        s--, t--;
        Query Q(s,t,k,i);
        queries[i] = Q;
    }

    sort(all(queries), cmp);
    vector< int > ans(q);
    lli curr = 1;

    for(int i = 0; i<q; i++)
    {
        Query C = queries[i];
        lli diff = C.k - curr;
        if(diff > 0)
        {
            //T = T * (A^diff);
            expB(diff);
            mult(3);
            curr = C.k;
        }
        ans[C.idx] = T[C.s][C.t];
    }
    for(int i = 0; i<q; i++)
    {
        printf("%d\n", ans[i]);
    }
    
    

    return 0;
}