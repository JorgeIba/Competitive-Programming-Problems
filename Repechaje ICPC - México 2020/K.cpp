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

int main(){
  int n, m;
  cin >> n >> m;
  VLL A(n), B(m);
  forn(i, n) cin >> A[i];
  forn(i, m) cin >> B[i];
  int j = 0;
  lli ans = 0;
  for(int i = 0; i < n; i++){
    while(B[j] < A[i]){
      ans += B[j];
      j++;
    }
    B[j] -= A[i];
  }
  for(; j < m; j++)
    ans += B[j];
    cout << ans << endl;
  return 0;
}