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

const lli MOD = (1LL<<31) - 1;

lli binPow(lli a, lli b)
{
  lli res = 1;
  a %= MOD;
  
  while(b)
  {
    if(b&1) res = res * a % MOD;
    b>>=1;
    a = a*a %MOD;
  }
  return res;
}


int main () {
	fastIO();
  lli t; cin>>t;
  while(t--)
  {
    lli n; cin>>n;
    n %= MOD;
    lli ans = n*(n+1) % MOD;
    lli aux = ((2*n+1)%MOD) * binPow(3, MOD-2) % MOD;
    ans = ans*(1 + aux) % MOD;
    ans = ans * binPow(4, MOD-2) % MOD;
    cout << ans << endl;
  }

    
	return 0;
}