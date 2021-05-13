#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,n) for(int i = a; i <= n; i++)
#define all(v) v.begin(), v.end()
#define se second
#define fi first
#define pb push_back
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
 
using namespace std; 

typedef pair<lli, lli> plli;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<lli>> vvlli;
typedef vector<lli> vlli;
typedef vector<pii> vpii;
const int mod = 1e9+7;
const int MOD = 1e9+7;
const int mxn = (int)2e5+20;
const int maxN = (int)2e5+20;
vector<lli> fact(mxn+1,1), invFact(mxn+1,1), inv(mxn+1,1);

lli comb(int r, int k){
  if(r < 0 || k > r) return 0;
  return fact[r] * invFact[r-k] % MOD * invFact[k] % MOD;
}
void precal(){
  fact[1] = 1;
  for(lli i = 2; i < maxN; ++i){
        fact[i] = i*fact[i-1] %MOD;
        inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
        invFact[i] = (lli)inv[i]*invFact[i-1]%MOD;
  }
}

int main(){
	fastIO();
  precal();
  int t;
  cin >> t;
  while(t--){
    int n;
    cin >> n;
    cout << comb(2*n-1, n) << endl;
  }
	return 0;
}

