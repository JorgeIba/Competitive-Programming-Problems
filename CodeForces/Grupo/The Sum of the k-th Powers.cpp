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

const lli MOD = 1e9+7;

lli binPow(lli a, lli b)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = res*a % MOD;
        b>>=1;
        a = a*a % MOD;
    }
    return res;
}


int main () {
	fastIO();
    lli n, k; cin>>n>>k;

    lli degree = k+1;

    vector<lli> ys(degree+2);

    for(int i = 1; i<=degree+1; i++)
    {
        ys[i] = (ys[i-1] + binPow(i, k)) % MOD;
    }

    if(n <= degree+1)
    {
        cout << ys[n] << endl;
        return 0;
    }

    lli num = 1;
    for(int j = 1; j<=degree+1; j++)
        num = num*(n-j) % MOD;

    lli R = 0;
    lli auxDen = 1, l = 1, r = degree;
    for(lli i = 1; i<=degree+1; i++)
    {
        if(i==1)
        {
            for(int j = 1; j<=degree+1; j++)
            {
                if(i!=j)
                {
                    auxDen = auxDen * ( (i - j + MOD)%MOD ) %MOD;
                }
            }
        }
        else
        {
            auxDen = auxDen*binPow(MOD - r, MOD-2) % MOD * l % MOD;
            l++, r--;
        }

        lli tot_num = num * binPow(n-i, MOD-2) % MOD;

        R = (R + (ys[i] * tot_num % MOD * binPow(auxDen, MOD-2) % MOD)) % MOD;
    }

    cout << R << endl;
    
	return 0;
}