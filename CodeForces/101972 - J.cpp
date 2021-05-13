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


lli binPow(lli a, lli b)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = res * a;
        b>>=1;
        a = a*a;
    }
    return res;
}



int main () {
	fastIO();

    lli t; cin>>t;
    while(t--)
    {
        lli n; cin>>n;
        lli ans = 0;


        lli apagados = 0, encendidos = 0;
        while(n)
        {
            if(n&1)
            {
                ans += (binPow(2, apagados) - 1)*binPow(2, encendidos);
                encendidos++;
            }
            else
            {
                apagados++;
            }
            n>>=1;
        }
        
        cout << ans << endl;
    }
    
	return 0;
}