#include<bits/stdc++.h>
#define forn(i,n) for(int i = 0; i < n; i++)
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

typedef long double ld;
typedef long long int lli;
typedef vector<int> vi;

const lli mod = (1LL << 31) - 1;

int main(){
  lli a = 0, b = 1;
  set<lli> s;
  s.insert(a % mod); s.insert(b % mod);
  for(int i = 2; i <= 10000; i++){
    lli aux = (a + b) % mod;
    a = b;
    b = aux;
    s.insert(aux);
  }
  int t;
  cin >> t;
  while(t--){
    lli x;
    cin >> x;
    if(s.count(x % mod)) cout << "YES\n";
    else cout << "NO\n";
  }
  return 0;
}