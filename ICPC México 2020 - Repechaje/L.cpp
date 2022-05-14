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

vector<int> lowestPrime;
void lowestPrimeSieve(int n){
	lowestPrime.resize(n + 1, 1);
	lowestPrime[0] = lowestPrime[1] = 0;
	for(int i = 2; i <= n; ++i) lowestPrime[i] = (i & 1 ? i : 2);
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2)
		if(lowestPrime[i] == i)
			for(int j = i * i; j <= n; j += 2 * i)
				if(lowestPrime[j] == j) lowestPrime[j] = i;
}


set<lli> facts;

void getFactors(lli n, bool clear = true)
{
  if(clear) facts.clear();

  while(n>1)
  {
    lli lp = lowestPrime[n];
    facts.insert(lp);
    while(n%lp == 0) n /= lp;
  }
  return;
}


void solve()
{
  lli a, b; cin>>a>>b;
  getFactors(a);
  getFactors(b, false);
  cout << SZ(facts) << endl;
}

const int maxN = 1e7+5;

int main () {
	fastIO();
  lowestPrimeSieve(maxN);
  lli t; cin>>t;
  while(t--) solve();

	return 0;
}