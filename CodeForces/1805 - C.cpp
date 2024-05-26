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
	int n, m; cin>>n>>m;
	vector<lli> slopes(n);
	for(auto &k: slopes) cin>>k;
	
	vector< array<lli,3> > parabs(m);
	for(auto &p: parabs) cin>>p[0]>>p[1]>>p[2];
	
	
	
	sort(all(slopes));
	slopes.erase(  unique(all(slopes)), slopes.end() ); 
	
	auto find_slope = [&](lli a, lli b, lli c) {
		auto itr = lower_bound(all(slopes), b) - slopes.begin();


		for(int j = itr - 100; j <= itr+100; j++){
			if(!(0 <= j && j < n)) continue;
			auto k = slopes[j];
			
			if((b - k)*(b - k) < 4*a*c) {
				cout << "YES" << endl;
				cout << k << endl;
				return;
			}
		}

		cout << "NO" << endl;
		return;
	};
	
	
	for(int i = 0; i < m; i++){
		auto [a, b, c] = parabs[i];
		
		find_slope(a, b, c);		
	}	
}


int main () {
	//fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

