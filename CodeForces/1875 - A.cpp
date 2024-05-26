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
	lli a, b, n; cin>>a>>b>>n;
	vector<lli> nums(n);
	for(auto &x: nums) cin>>x;

	lli ans = 0;
	lli curr = b;
	for(auto x: nums){
		ans += (curr-1);
		curr = 1;
		curr = min(curr+x, a);
	}

	ans += curr;
	cout << ans << endl;


}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

