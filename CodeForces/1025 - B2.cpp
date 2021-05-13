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

set<lli> fact(lli n)
{
    set<lli> primes;
    for(lli i = 2; i*i <= n; i++)
    {
        while(n % i == 0)
        {
            n /= i;
            primes.insert(i);
        }
    }
    if(n>1) primes.insert(n);
    return primes;
}


int main () {
	fastIO();
    lli n; cin>>n;

    vector<pair<lli,lli>> nums(n);

    for(auto &x: nums) cin>>x.first>>x.second;

    auto primes_first = fact(nums[0].first);
    auto primes_second = fact(nums[0].second);
    primes_first.insert(all(primes_second));

    map<lli,lli> fr;
    for(auto x: primes_first) fr[x]++;


    for(int i = 1; i<n; i++)
    {
        lli num1 = nums[i].first, num2 = nums[i].second;
        for(auto &x: fr)
        {   
            lli prime = x.first;
            if( num1 % prime == 0|| num2 % prime == 0 )
                x.second++;
        }
    }

    for(auto x: fr)
    {
        if(x.second == n)
        {
            cout << x.first << endl;
            return 0;
        }
    }
    cout << -1 << endl;
	return 0;
}