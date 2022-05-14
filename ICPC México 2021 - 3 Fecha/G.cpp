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

const lli maxN = 80;
vector<lli> fib(maxN);
unordered_map<lli,bool> mem;

bool dp(lli n) {
    
  if(mem.find(n) != mem.end()) {
    return mem[n]; 
  } 
  
  bool ans = false;
  for(auto f: fib)
  {
    if(f <= 1) continue;
    if( n % f == 0 )
    {
      if( dp(n / f) )
      {
        ans = true;
        break;
      }  
    }
  }

  mem[n] = ans;
  return ans;
}


void build(lli n, string &ans)
{
  for(int i = maxN-1; i>= 2; i--)
  {
    if( n % fib[i] == 0 && dp(n / fib[i]))
    {
      string fib_s(i, 'A');
      fib_s[i-1] = 'B';
      ans += fib_s;

        if(n/fib[i] == 1)
        return;

      build(n / fib[i], ans);
      return;
    }
  }
}

    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
lli aleatorio(lli a, lli b){
	std::uniform_int_distribution<lli> dist(a, b);
	return dist(rng);
}


int main () {
  fastIO();


  fib[0] = fib[1] = 1;


  for(lli i = 2; i<maxN; i++)
  {
    fib[i] = (fib[i-1] + fib[i-2]);
  }

  for(auto x: fib) mem[x] = true;
  
  


  lli N;
  cin >> N;
  if(!dp(N)) cout << "IMPOSSIBLE\n";
  else 
  {
    string ans;
    build(N, ans);
    cout << ans << endl;
  }

	return 0;
}

