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
	vector<int> nums(n);
	for(auto &x: nums) cin>>x;

	vector<bool> check(2*n+5);

	vector<int> ans(n);
	int mx = 0;
	for(int i = 0; i < n; i++){
		auto x = nums[i];
		for(int j = 1; j <= 2*n; j++){
			if(check[j] == false && j > mx && j != x){
				ans[i] = j;
				break;
			}
		}

		x = ans[i];
		check[x] = 1;
		mx = x;
	}

	cout << ans.back() << endl;
}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

