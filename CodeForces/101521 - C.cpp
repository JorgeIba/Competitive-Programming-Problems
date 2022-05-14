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

lli N, R, K, M;


map<lli,lli> factorize(lli n) {
  map<lli,lli> factors;
  for(lli i = 2; i * i <= n; i++) {
    while(n % i == 0) {
      factors[i]++;
      n /= i;
    }
  }
  if(n > 1) factors[n]++;
  return factors;
}

void fill(VLL& v){
  set<lli> used;
  for(auto i:v)
    used.insert(i);
  for(lli d = 1; d * d <= K; d++){
    if(K % d) continue;

    if(!used.count(d) && d <= R){
      v.push_back(d);
      used.insert(d);
    }

    if(!used.count(K / d) && (K / d) <= R){
      v.push_back(K / d);
      used.insert(K / d);
    }
  }
}

//M -> cantidad de factores distintos
vector<bool> possibleMerge;

lli dp[1<<13];

lli f(lli mask) {
    if( __builtin_popcountll(mask) == M) return 0;

    lli &ans = dp[mask];
    if(ans != -1) return ans;
  
    ans = 1e18;
    for(lli new_mask = 0; new_mask < (1 << M); new_mask++) {
      if(mask == new_mask) continue;
      
      if((mask & new_mask) == 0 && possibleMerge[new_mask]) {//disjuntos
        ans = min(ans, 1 + f(mask | new_mask) );
      }
    }
    return ans;
}



void build_ans(lli mask, VLL& ans) {
    if( __builtin_popcountll(mask) == M) return;

    lli best_dp = 1e18, best_mask = 0;

    for(lli new_mask = 0; new_mask < (1 << M); new_mask++) {
      if(mask == new_mask) continue;
      
      if((mask & new_mask) == 0 && possibleMerge[new_mask]) {//disjuntos
        lli aux = 1 + f(mask | new_mask);
        if(aux < best_dp) {
            best_dp = aux;
            best_mask = new_mask;
        }
      }
    }

    ans.push_back(best_mask);
    build_ans(mask | best_mask, ans);

    return;
}



int main () {
	//fastIO();
  memset(dp, -1, sizeof(dp));
  cin >> N >> R >> K;
  auto fact = factorize(K);

    vector<pair<lli,lli>> factors;
    for(auto x: fact) factors.push_back(x);    

    M = SZ(factors); 

    possibleMerge.resize(1<<M);
    for(int mask = 0; mask < (1<<M); mask++) {
        lli product = 1;
        for(int j = 0; j < M; j++) {
            if((1<<j) & mask)
                product *= binPow(factors[j].first, factors[j].second);
                
        }
        possibleMerge[mask] = (product <= R);
    }

    lli mini = f(0);

    if(mini > N) {
        cout << -1 << endl;
        return 0;
    }

    VLL ans_mask;
    build_ans(0, ans_mask);

    VLL ans;
    for(auto mask: ans_mask) {
        lli product = 1;
        for(int j = 0; j < M; j++) {
            if((1<<j) & mask)
                product *= binPow(factors[j].first, factors[j].second);
        }
        ans.push_back(product);
    }

  fill(ans);


  if(SZ(ans) >= N){
    for(int i = 0; i < N; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
  }
  else
    cout << -1 << endl;
    
	return 0;
}

