
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
	lli n, x, p; cin>>n>>x>>p;
	vector<lli> ans;
	
	for(lli i = 1; i <= 2*n; i++){
		lli sum = (i * (i+1)) / 2;
		if(sum % n == (n - x) % n) {
			ans.push_back(i);
		}
	}
	
	sort(all(ans));
	if(ans.empty()) cout << "No" << endl;
	else {
		if(ans[0] <= p) {
			lli sum = ((ans[0] * (ans[0] + 1))) / 2;
			assert((sum + x) % n == 0);
			cout << "Yes" << endl;
		} else {
			cout << "No" << endl;
		}
	}
	
}

int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}
 