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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
lli aleatorio(lli a, lli b){
	std::uniform_int_distribution<lli> dist(a, b);
	return dist(rng);
}


int main () {
	fastIO();
    lli n; cin>>n;

    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;
	

    lli ans = 1;
    for(int t = 0; t<15; t++)
    {
        lli A = nums[aleatorio(0, n-1)];
        unordered_map<lli,lli> fr;

        for(int i = 0; i<n; i++)
        {
            fr[ __gcd(A, nums[i]) ]++;
        }

        for(auto dd: fr)
        {
            lli g = dd.first;
            if(g < ans) continue;

            lli how_much = 0;
            for(auto dd2: fr)
            {
                if( dd2.first % g == 0 )
                {
                    how_much += dd2.second;
                }
            }

            if(2*how_much >= n) ans = max(ans, g);
        }
    }


    cout << ans << endl;

	return 0;
}

