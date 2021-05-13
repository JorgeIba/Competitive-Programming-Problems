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

const lli MOD = 1e9;

lli binPow(lli a, lli b)
{
  lli res = 1;
  a %= MOD;
  if(a < 0) a += MOD;
  while(b)
  {
    if(b&1) res = res * a %MOD;
    b>>=1;
    a = a * a %MOD;
  }
  return res;
}


void solve()
{
  lli k, q; cin>>k>>q;
  vector<lli> init(k);
  for(auto &x: init) cin>>x;

  while(q--)
  {
    lli n; cin>>n;
    lli place = init[n%k];
    lli exp = n / k;
    cout << binPow(place, exp+1) << endl;
  }

}


int main () {
	fastIO();
  lli t; cin>>t;
  while(t--) solve();

    
	return 0;
}