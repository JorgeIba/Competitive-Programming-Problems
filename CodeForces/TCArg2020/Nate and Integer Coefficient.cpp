#include <bits/stdc++.h>
#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli MOD = 1e9 + 7;

lli T[2][2], V[2][1], I[2][2], C[2][2], A[2][2];


void binPow(lli e)
{
    for(int i = 0; i<2; i++)
    {
        for(int j = 0; j<2; j++)
        {
            I[i][j] = (i==j? 1: 0);
            A[i][j] = T[i][j];
        }
    }
    while(e)
    {
        if(e&1) // I = I*A
        {
            forn(i,0,2)
            {
                forn(j,0,2)
                {
                    C[i][j] = 0;
                    {
                        forn(k,0,2)
                        {
                            C[i][j] = (C[i][j] + A[i][k]*I[k][j])%MOD;
                            if(C[i][j] < 0) C[i][j]+=MOD;
                        }
                    }
                }
            }
            forn(i,0,2) forn(j,0,2) I[i][j] = C[i][j];
        }
        e>>=1;
        forn(i,0,2) // A = A*A
        {
            forn(j,0,2)
            {
                C[i][j] = 0;
                {
                    forn(k,0,2)
                    {
                        C[i][j] = (C[i][j] + A[i][k]*A[k][j])%MOD;
                        if(C[i][j] < 0) C[i][j]+=MOD;
                    }
                }
            }
        }
        forn(i,0,2) forn(j,0,2) A[i][j] = C[i][j];
    }

    forn(i,0,2) forn(j,0,2) T[i][j] = I[i][j];
}

void mult()
{
    forn(i,0,2)
    {
        forn(j,0,1)
        {
            C[i][j] = 0;
            {
                forn(k,0,2)
                {
                    C[i][j] = (C[i][j] + T[i][k]*V[k][j])%MOD;
                    if(C[i][j] < 0) C[i][j]+=MOD;
                }
            }
        }
    }
    forn(i,0,2) forn(j,0,2) V[i][j] = C[i][j];
}

void solve()
{
    lli a, n; cin >> a >> n;
    a = a%MOD;

    //Matrix<lli> T(2, 2);
    T[0][0] = a;
    T[0][1] = -1;
    T[1][0] = 1;
    T[1][1] = 0;
    //Matrix<lli> V(2,1);
    V[0][0] = a;
    V[1][0] = 2;

    n = abs(n); //f(k) = f(-k)
    if(n == 0) cout << 2 << endl;
    else if(n == 1) cout << a << endl;
    else
    {
        binPow(n-1);
        mult();
        cout << V[0][0] << endl;
        //cout << dp[n] << endl;
    }
    return;
}



int main()
{
    //fastIO();
    lli t; cin>>t;
    while(t--) solve();

    return 0;
}