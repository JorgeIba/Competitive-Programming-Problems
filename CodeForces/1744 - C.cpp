
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


void solve(){
	lli n; cin>>n;
	char q; cin>>q;
	string s; cin>>s;
	
	string ss = s+s;
	
	if(q == 'g') {
		cout << 0 << endl;
		return;
	}

	map<lli,lli> last;
	for(int i = ss.length() - 1; i >= n; i--) {
		if(ss[i] == 'g')
			last['g'] = i;
	}
	
	vector<lli> ans(n);
	for(int i = n-1; i>= 0; i--) {
		ans[i] = last['g'];
		
		if(ss[i] == 'g') last['g'] = i;
	}
	
	
	lli ans_x = -1;
	for(int i = 0; i < n; i++){
		if(ss[i] == q) {
			ans_x = max(ans_x, ans[i] - i);
		}
	}
	cout << ans_x << endl;
}


int main () {
	//fastIO();
	int t; cin>>t;
	
	while(t--) solve();

	return 0;
}

