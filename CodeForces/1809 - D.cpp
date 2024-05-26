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

typedef vector<int> vi;
#define pb push_back


struct WaveletTree{
	int low,high;
	WaveletTree *left, *right;
	vi mapLeft;

	WaveletTree( vi::iterator from, vi::iterator to, int x, int y ): low(x), high(y){
		if(from >= to) return;
		int m = (low+high)/2;
		auto f = [m](int x){ return x <= m; };
		mapLeft.reserve( to-from+1 );
		mapLeft.pb(0);
		for(auto it=from; it!=to; it++){
			auto leq = f(*it);
			mapLeft.pb( mapLeft.back()+ leq );
		}
		if(high != low){
			auto pivot = stable_partition(from,to,f);
			left = new WaveletTree(from,pivot,low,m);
			right = new WaveletTree(pivot,to,m+1,high);
		}
	}

	//number of elements equal to k in [l, r]
	int equalTo(int l, int r, int k){
		if(l > r || k < low || k > high)
			return 0;
		if(low == high)
			return r - l + 1;
		int lb = mapLeft[l - 1], rb = mapLeft[r];
		int m = (low + high) / 2;
		if(k <= m)
			return left->equalTo(lb + 1, rb, k);
		else 
			return right->equalTo(l - lb, r - rb, k);
	}
};


lli cost = 1'000'000'000'000;

void main_(){
	string s; cin>>s;
	int n = SZ(s);
	vector<int> nums(n+2);
	
	nums[0] = 0;
	nums[n+1] = 1;
	for(int i = 1; i <= n; i++) {
		nums[i] = s[i-1] - '0';
	}	
	
	auto nums_wav = nums;
	WaveletTree *WT = new WaveletTree(all(nums_wav), *min_element(all(nums_wav)), *max_element(all(nums_wav)));
	
	lli ans = (cost+1) * n;
	
	for(int i = 0; i <= n; i++) {
		lli ones_left  = WT->equalTo(0 + 1, i + 1, 1);
		lli zeros_right = WT->equalTo(i+1 + 1, n+1 + 1, 0);
		
		ans = min(ans, (cost+1) * ones_left + (cost+1) * zeros_right);

		if(nums[i] == 1 && nums[i+1] == 0) {
			zeros_right--;
			ones_left--;

			ans = min(ans, cost + (cost+1) * ones_left + (cost + 1) * zeros_right);
		} 
	}

	cout << ans << endl;
}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

