#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

void main_(){
	int n, m, k; cin>>n>>m>>k;
	vector<lli> fr(m);
	for(auto &x: fr) cin>>x;
	
	bool ans = true;
		
	lli maxi = *max_element(all(fr));
	lli how_many_maxi = count(all(fr), maxi);
	
	lli blocks = n / k;
	
	// cout << maxi << " - " << how_many_maxi << " " << blocks << endl;
	if(maxi <= blocks) {
		
	} else {
		if(maxi == blocks + (n % k != 0)) {
			if( n % k < how_many_maxi ) ans = false;
		} else {
			ans = false;
		}
	}
	

	
	cout << (ans ? "YES" : "NO") << endl;
		
}


int main () {
	//fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

