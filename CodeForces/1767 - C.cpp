// Problem: C. Count Binary Strings
// Contest: Codeforces - Educational Codeforces Round 140 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1767/problem/C
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

vector<vector<int>> constr;

const lli MOD = 998244353;
lli dp[110][110][2];

lli fun(int idx, int idx_last_different, int last) {

	for(int i = idx_last_different; i < idx; i++) {
		if(constr[i][idx-1] == 2) {
			return 0;
		}
	}
	
	for(int i = 0; i < idx_last_different; i++){
		if(constr[i][idx-1] == 1){
			 return 0;
		}
	}
	
	lli &ans = dp[idx][idx_last_different][last];
	if(ans != -1) return ans;
	
	if(idx == SZ(constr)) return ans = 1;

	ans = 0;
	if(last == 0) {
		ans = (fun(idx+1, idx_last_different, 0) + fun(idx+1, idx, 1)) % MOD;
	} else {
		ans = (fun(idx+1, idx_last_different, 1) + fun(idx+1, idx, 0)) % MOD;
	}
		
	return ans;
}




void main_(){
	int n; cin>>n;

	constr.assign(n, vector<int>(n));
	for(int i = 0; i < n; i++){
		for(int j = i; j < n; j++) {
			cin>>constr[i][j];
		}
	}
	
	memset(dp, -1, sizeof(dp));
	lli ans = (fun(1, 0, 0) + fun(1, 0, 1)) % MOD;
	cout << ans << endl;
	
}


int main () {
	//fastIO();
	
	int t = 1; 
//	cin>>t;
	while(t--) 
		main_();


	return 0;
}

