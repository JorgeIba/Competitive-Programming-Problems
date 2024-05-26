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
  string s;
  cin >> s;
  // vector<int> last(s.size());
  int last = -1;
  int ans = 0;
  int max_dis = -1;
  for(int i = s.size() - 1; i>=0; i--) {
    if(s[i] == '1') {
      if(last != -1) {
        max_dis = max(max_dis, last - i - 1);
      }
      last = i;
    }
  }
  if(max_dis & 1) max_dis++;
  ans = max(ans, max_dis / 2);
  cout << ans << endl;
  return 0;
}

