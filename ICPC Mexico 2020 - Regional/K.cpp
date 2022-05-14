#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,n) for (int i = a; i <= n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define fi first
#define se second

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> vi;
typedef pair<int,int> pii;


lli K, L, n;
vector<lli> delays;
vector< vector<lli> > T;

const int maxK = 720 + 10;
const lli MOD = 1e9+7;

pii bin_search(int i, int mini, int maxi) {
	int l = 0, r = K-1;
	int sup = -1, inf = -1;
	while(l <= r) {
		int mid = (l+r)/2;
		if(T[i][mid] > maxi) {
			r = mid - 1;
		}
		else {
			sup = mid;
			l = mid + 1;
		}
	}
	l = 0, r = K-1;
	while(l <= r) {
		int mid = (l+r)/2;
		if(T[i][mid] < mini)
			l = mid + 1;
		else {
			inf = mid;
			r = mid - 1;
		}
	}
	return {inf, sup};
}

int main () {
	fastIO();

  cin >> K >> L;
  T.resize(K, vector<lli>(K));
  forn(i,K) {
    forn(j,K){
      cin >> T[i][j];
    }
  }
  cin >> n;
  delays.resize(n);
  forn(i,n-1) cin >> delays[i];

  lli ans = 0;
  vi dp_ant(K);
  forn(i,K) {
	  dp_ant[i] = 1;
	  if(i > 0) dp_ant[i] += dp_ant[i-1];
  }
  for(int i = n-2; i >= 0; i--) { // itera sobre el delay
  	  vi dp_act(K);
	  for(int j = 0; j < K; j++) { // el vato en el que vas
		  pii lims = bin_search(j, delays[i] -L, delays[i]+L);
		  // cout << lims.fi << ' '<< lims.se << '\n';
		  if(lims.fi == -1 || lims.se == -1) continue;
		  dp_act[j] = (dp_ant[lims.se] - (lims.fi > 0? dp_ant[lims.fi-1] : 0) + MOD)%MOD;
	  }
	  forr(i,1,K-1) {
		  dp_act[i] += dp_act[i-1];
		  if(dp_act[i] >= MOD) dp_act[i] -= MOD;
	  }
	  dp_ant = dp_act;
  }
  cout << dp_ant[K-1] << endl;
	return 0;
}
