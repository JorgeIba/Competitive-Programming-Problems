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

map<lli,lli> get_factors(lli n)
{
	map<lli,lli> factors;

	while(n > 1)
	{
		lli lowest_n = lowestPrime[n];
		while( n % lowest_n == 0 )
		{
			factors[lowest_n]++;
			n /= lowest_n;
		}
	}

	return factors;
}


lli n, k;

map<lli,lli> get_complements(map<lli,lli> &factors)
{
	map<lli,lli> complements;
	for(auto x: factors)
	{
		complements[x.first] = (k - x.second);
	}
	return complements;
}





const int maxN = 1e5 + 100;


int main () {
	//fastIO();

	lowestPrimeSieve(maxN);

	cin>>n>>k;

	vector<lli> nums(n);
	for(auto &x: nums) cin>>x;


	lli ans = 0;
	map<map<lli,lli>,lli> fr;
	for(int i = 0; i<n; i++)
	{
		auto factors = get_factors(nums[i]);
		auto copy_factors = factors;

		for(auto x: copy_factors)
		{
			if(x.second % k == 0)
			{
				factors.erase(x.first);
			}
			else{
				factors[x.first] = (x.second % k);
			}
		}

		auto complement = get_complements(factors);

		ans += fr[complement];

		fr[factors]++;
	}

	cout << ans << endl;

	return 0;
}

