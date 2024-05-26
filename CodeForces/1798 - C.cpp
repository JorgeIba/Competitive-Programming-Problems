#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;


void main_(){
	int n; cin>>n;
	vector< pair<lli,lli> > candies(n);

	for(auto &x: candies) cin>>x.first>>x.second;

	auto lcm = [](lli a, lli b) {
		return a * (b / gcd(a, b));
	};

	lli ans = 1;
	lli g = 0, l = 1;
	for(int i = 0; i < n; i++) {
		auto [a, b] = candies[i];
		if(gcd(g, a*b) % lcm(l, b)) {
			ans++;
			g = 0, l = 1;
		}

		g = gcd(g, a*b);
		l = lcm(l, b);
	}

	cout << ans << endl;
}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

