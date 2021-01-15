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

const int MOD = 1e9+7;

lli binPow(int a, int b)
{
    lli res = 1; 
    while(b)
    {
        if(b&1) res = (1LL*res*a)%MOD;
        b>>=1;
        a = (1LL*a*a)%MOD;
    }
    return res;
}


int main () {
	//fastIO();
    int n, k; cin>>n>>k;
    lli suma = 0;
    for(int i = 0; i<n; i++)
    {
        suma += binPow(k, __gcd(i, n));
        if(suma >= MOD) suma -= MOD;
    }
    suma = (suma*binPow(n, MOD-2))%MOD;
    cout << suma << endl;
    
	return 0;
}