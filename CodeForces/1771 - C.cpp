// Problem: C. Hossam and Trainees
// Contest: Codeforces - Codeforces Round #837 (Div. 2)
// URL: https://codeforces.com/contest/1771/problem/C
// Memory Limit: 256 MB
// Time Limit: 3000 ms
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


//20
vector<lli> primes;
vector<bool> isPrime;
void primesSieve(int n)
{
	isPrime.resize(n + 1, true);
	isPrime[0] = isPrime[1] = false;
	primes.push_back(2);
	for(int i = 4; i <= n; i += 2) isPrime[i] = false;
	for(lli i = 3; i <= n; i += 2)
    {
		if(isPrime[i])
        {
			primes.push_back(i);
			if(i * i <= n)
				for(lli j = i * i; j <= n; j += 2 * i)
					isPrime[j] = false;
		}
	}
}



vector<lli> factorize(lli n) {
	vector<lli> facts;
	
	for(auto p: primes){
		if(n % p == 0) {
			facts.push_back(p);
			while(n % p == 0) n/=p;
		}
	}
	
	
	if(n > 1) facts.push_back(n);
	
	return facts;
}



void main_(){
	lli n; cin>>n;
	vector<lli> nums;
	
	for(int i = 0; i < n; i++){
		lli x; cin>>x;
		if( x == 1 ) continue;
		nums.push_back(x);
	}

	vector<lli> primes_dist;	
	
	for(auto x: nums) {
		auto facts = factorize(x);
		for(auto p: facts) 
			primes_dist.push_back(p);
	}
	
	
	set<lli> primes_s;
	for(auto p: primes_dist) {
		if(primes_s.count(p)) {
			cout << "YES" << endl;
			return;
		}
		primes_s.insert(p);
	}
	
	
	cout << "NO" << endl;
}


int main () {
	//fastIO();

	lli sqrt = sqrtl(1e9);
	primesSieve(sqrt+1);

	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

