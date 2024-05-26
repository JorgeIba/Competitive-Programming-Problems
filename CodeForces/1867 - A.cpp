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
	int n; cin>>n;
	vector< pair<int,int> > nums(n);
	forn(i, n) {
		cin>>nums[i].first;
		nums[i].second = i;
	}

	sort(all(nums)); reverse(all(nums));
	vector<int> ans(n);
	forn(i, n){
		ans[nums[i].second] = i+1;
	}
	for(auto x: ans) cout << x << " ";
	cout << endl;

}


int main () {
	//fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

