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


int main () {
	fastIO();
	int n; cin>>n;
	vector<lli> nums(n);
	for(auto &x: nums) cin>>x;


	vector<lli> prefix_sum(n);
	for(int i = 0; i<n; i++)
	{
		prefix_sum[i] = (i>0? prefix_sum[i-1] : 0) + nums[i]; // condicion? si es verdadero : si es falso
	}

	int q; cin>>q;
	while(q--)
	{
		int l, r; cin>>l>>r;
		cout << prefix_sum[r] - (l > 0? prefix_sum[l-1] : 0) << endl;
	}

	return 0;
}