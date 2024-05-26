#include<bits/stdc++.h>
#define lli long long int
#define ld long double
#define forn(i,n) for(int i = 0; i < n; i++)
#define forr(i,a,n) for(int i = a; i <= n; i++)
#define fi first
#define se second
#define pb push_back
#define all(v) v.begin(),v.end()
#define SZ(v) (int)v.size()
#define endl '\n'
#define fastIO() ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<lli> vlli;

int main() {
  fastIO();
  vector<lli> prec(10);
  prec[0] = 1;
  forr(i,1,9) prec[i] = i * prec[i - 1];
  lli y;
  cin >> y;
  int curr = 9;
  vector<int> ans;
  if(y == 1) {
    cout << "0" << endl;
    return 0;
  }
  while(true) {
    if(y == 0) break;
    if(prec[curr] > y) {
      curr--;
    }
    else {
      y-= prec[curr];
      ans.pb(curr);
    }
  }
  reverse(all(ans));
  for(int x : ans) cout << x; cout << endl;
  return 0;
}

