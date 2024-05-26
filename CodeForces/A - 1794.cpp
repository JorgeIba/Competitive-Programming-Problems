// Problem: A. Prefix and Suffix Array
// Contest: Codeforces - Codeforces Round 856 (Div. 2)
// URL: https://codeforces.com/contest/1794/problem/0
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

auto check_opt = [](string ss_1, string ss_2) {	
	auto aux_1 = ss_1;
	auto aux_2 = ss_2;
	
	ss_1.erase(ss_1.begin());
	ss_2.pop_back();
	
	if(ss_1 != ss_2) {
		swap(aux_1, aux_2);
	}
	
	auto total = aux_1 + aux_2.back();
	auto reversed_total = total;
	reverse(all(reversed_total));
	return total == reversed_total;
};

void solve(){
	int n; cin>>n;
	vector< string > ss(2*n - 2);
	for(auto &s: ss) cin>>s;
	
	
	sort(all(ss), [](string s1, string s2){
		return SZ(s1) > SZ(s2);
	});
	
	
	string s_1 = ss[0];
	string s_2 = ss[1];

	int m = SZ(s_1);	
	assert(m == n-1);
	assert(SZ(s_2) == m);
	

	if(check_opt(s_1, s_2)) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}
	
}

int main () {
	//fastIO();
	

	int t; cin>>t;
	while(t--) solve();


	return 0;
}

