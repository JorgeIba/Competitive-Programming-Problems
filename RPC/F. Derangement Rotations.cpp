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

lli MOD;

lli binPow(lli a, lli b)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = res * a % MOD;
        b>>=1;
        a = a*a%MOD;
    }
    return res;
}

int main () {
	//fastIO();
	
  lli n; cin>>n>>MOD;
  
  lli ans = 0;
  for(lli d = 2; d<n; d++)
  {
    lli ciclos = __gcd(d,n);
    ans += (binPow(2, ciclos-1) - 1)*(n-2) % MOD;
    if(ans >= MOD) ans -= MOD;
  }

  cout <<ans<< endl;

	return 0;
}
