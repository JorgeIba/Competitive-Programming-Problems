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

void solve()
{
  lli q; cin>>q;
  stack<lli> minimum, maximum, normal;

  while(q--)
  {
    lli t; cin>>t;
    if(t==1) // push
    {
      lli v; cin>>v;
      normal.push(v);
      if(minimum.empty() || v < minimum.top())
        minimum.push(v);
      else 
        minimum.push(minimum.top());

      if(maximum.empty() || v > maximum.top())
        maximum.push(v);
      else
        maximum.push(maximum.top());
    }
    else if(t == 2) // pop
    {
      if(normal.empty()) continue;
      normal.pop();
      minimum.pop();
      maximum.pop();
      
    }
    else //min - max
    {
      if(normal.empty()) cout << "Empty!" << endl;
      else cout << abs( maximum.top() -  minimum.top() ) << endl;
    }
  }


}


int main () {
	fastIO();
  lli t; cin>>t;
  while(t--) solve();

	return 0;
}