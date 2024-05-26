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
  int x;
  cin >> x;
  int a = -2, b = 1, c = -14, d = 17;
  if(x <= -3) {
    x = x + 4;
    x = x * x;
    cout << -x + 8 << endl;
  }
  else if(x <= 2 && x > -3) {
    cout << a*x + b << endl;
  }
  else {
    cout << x*x*x + c * x + d << endl;
  }
  return 0;
}

