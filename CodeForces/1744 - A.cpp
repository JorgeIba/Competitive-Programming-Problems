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
	
	vector<lli> nums(n);
	for(auto &x: nums) cin>>x;
	
	string asd; cin>>asd;

	for(int i = 0; i < n; i++){
		for(int j = i+1; j < n; j++){
			if(nums[j] == nums[i]) {
				if(asd[i] != asd[j]){
					cout << "NO\n";
					return;
				}
			}
		}
	}
	cout << "YES\n";
	
}


int main () {
	//fastIO();
	int t; cin>>t;
	
	while(t--) solve();

	return 0;
}

