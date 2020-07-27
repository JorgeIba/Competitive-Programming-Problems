#include <bits/stdc++.h>
#define lli int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli INF = 1e9;

const lli maxN = 305;
lli T[maxN][maxN], A[maxN][maxN], I[maxN][maxN], C[maxN][maxN];
lli n, m; 


void matExp(lli e)
{   
    while(e)
    {
        if(e&1) //I = I*A;
        {
            for(int i = 0; i<n; i++)
                for(int j = 0; j<n; j++)
                {
                    C[i][j] = -INF;
                    for(int k = 0; k<n; k++)
                    {
                        lli poss = (I[i][k] + A[k][j]);
                        C[i][j] = (C[i][j] < poss ? poss : C[i][j]);
                    }
                }
            forn(i,0,n) forn(j,0, n) I[i][j] = C[i][j];
        } 
        
        //A = A*A;
        
        for(int i = 0; i<n; i++)
            for(int j = 0; j<n; j++)
            {
                C[i][j] = -INF;
                for(int k = 0; k<n; k++)
                {
                    lli poss = (A[i][k] + A[k][j]);
                    C[i][j] = (C[i][j] < poss ? poss : C[i][j]);
                }
            }
        forn(i,0,n) forn(j,0,n) A[i][j] = C[i][j];   
        e>>=1;
    }
}


bool checkCycle(lli &mid)
{
    forn(i,0,n) forn(j,0,n) 
    {
        I[i][j] = (i==j? 0: -INF);
        A[i][j] = T[i][j];
    }

    matExp(mid);

    for(int i = 0; i<n; i++)
    {
        if(I[i][i] > 0) return true;
    }
    return false;
}


int main()
{
    fastIO();
    scanf("%ld%ld", &n, &m);
    //cin>>n>>m;
    forn(i,0,n) forn(j,0,n)
        T[i][j] = (i==j? 0: -INF);

    forn(a,0,m)
    {
        lli i, j;
        //cin>>i>>j;
        scanf("%ld%ld",&i,&j);
        i--, j--;
        scanf("%ld%ld", &T[i][j], &T[j][i]);
        //cin>>T[i][j]>>T[j][i];
    }


    lli l = 1, r = n, res = -1;
    while(l<=r)
    {
        lli mid = l + ((r-l)>>1);
        if( checkCycle( mid  )  )
        {
            res = mid;
            r = mid-1;
        }
        else l = mid + 1;
        
    }
    
    cout << (res==-1? 0: res) << endl;

    return 0;
}