// Problem: D. Lucky Chains
// Contest: Codeforces - Educational Codeforces Round 139 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1766/problem/D
// Memory Limit: 512 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

//12
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


vector<lli> get_primes(lli n){
	vector<lli> primes;
	while(n>1) {
		lli lp = lowestPrime[n];
		primes.push_back(lp);
		while(n % lp == 0) {
			n /= lp;
		}
	}
	
	return primes;
}



void main_(){
	lli x, y; cin>>x>>y;
	
	lli diff = y-x;
	
	if(diff == 1) {
		cout << -1 << endl;
		return;
	}
	
	auto primes = get_primes(diff);
	lli k = 1e9;
	
	for(auto p: primes) {
		lli modu = x % p;
		if(modu == 0) k = 0;
		else {
			lli diff_mod = p - modu;
			k = min(k, diff_mod);
		}
	}
	
	cout << k << endl;
}


int main () {
	fastIO();
	const int maxN = 1e7+5;
	lowestPrimeSieve(maxN);
	
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

