#include<bits/stdc++.h>
#define forn(i,n) for(int i = 0; i < n; i++)
#define fi first
#define se second
#define fastIO() ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define lli long long int
#define all(v) v.begin(),v.end()
#define endl '\n'

using namespace std;

vector<pair<lli,pair<lli,lli>>> fac;
lli mini = 0, maxi = 0, ini = 0;
int k;

void solve() {
  lli L, T;
  cin >> T >> L;
  if(L < mini || L > maxi) {
    cout << "no" << endl;
    return;
  }
  lli aux_min = ini;
  lli aux_max = ini;
  lli curr = mini;

  forn(i,k) {
    aux_min += min(fac[i].se.se - fac[i].se.fi, L - curr)*fac[i].fi;
    curr += min(fac[i].se.se - fac[i].se.fi, L - curr);
    if(curr == L) break;
  }

  curr = mini;
  for(int i = k - 1; i >= 0; i--) {
    aux_max += min(fac[i].se.se - fac[i].se.fi, L - curr)*fac[i].fi;
    curr += min(fac[i].se.se - fac[i].se.fi, L - curr);
    if(curr == L) break;
  }

  if(T*L >= aux_min && T*L <= aux_max) {
    cout << "yes" << endl;
  }
  else
    cout << "no" << endl;
}


int main() {
  fastIO();
  cin >> k;
  fac.resize(k);
  forn(i,k) {
    cin >> fac[i].fi >> fac[i].se.fi >> fac[i].se.se;
    mini += fac[i].se.fi;
    maxi += fac[i].se.se;
    ini += fac[i].se.fi * fac[i].fi;
  }
  //cout << "aux: " << mini << ' ' << maxi << endl;
  sort(all(fac));

  int tt;
  cin >> tt;
  while(tt--) {
    // cout << "test: " << tt << ": ";
    solve();
  }
  return 0;
}