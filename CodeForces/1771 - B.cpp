#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

void main_(){
	lli n, m; cin>>n>>m;
	
	vector<array<lli, 2>> ranges(n+1);
	
	for(lli i = 1; i <= n; i++) {
		ranges[i][0] = 0;
		ranges[i][1] = n+1;
	}
	
	for(lli i = 0; i < m; i++){
		lli a, b; cin>>a>>b;
		if(a > b) swap(a, b);
		
		ranges[a][1] = min(ranges[a][1], b);
		ranges[b][0] = max(ranges[b][0], a);
	}
	
	
	for(lli i = n-1; i >= 1; i--) {
		ranges[i][1] = min(ranges[i][1], ranges[i+1][1]);
	}
	
	lli ans = 0;
	for(lli i = 1; i <= n; i++) {
		ans += (ranges[i][1] - 1) - i + 1;
	}
	
	cout << ans << endl;
}


int main () {
	//fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

