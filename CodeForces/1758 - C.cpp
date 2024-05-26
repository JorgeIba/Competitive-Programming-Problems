// Problem: C. Almost All Multiples
// Contest: Codeforces - Codeforces Round #836 (Div. 2)
// URL: https://codeforces.com/contest/1758/problem/C
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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
	int n, x; cin>>n>>x;
	
	if(n % x != 0 || x > n) {
		cout << -1 << endl;
		return;
	}
	
	vector<lli> ans(n+1);
	iota(all(ans), 0);
	
	ans[1] = x; ans[x] = n; ans[n] = 1;	

	int curr = x;
	for(int k = 2; k < n; k++) {
		if(k % curr == 0 && n % k == 0) {
			swap(ans[curr], ans[k]);
			curr = k;
		}
	}
	
	for(int i = 1; i <= n; i++) cout << ans[i] << " ";
	cout << endl;
	
	for(int i = 1; i <= n-1; i++) {
		assert(ans[i] % i == 0);
	}

}


int main () {
	//fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

