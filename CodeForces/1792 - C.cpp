// Problem: C. Min Max Sort
// Contest: Codeforces - Educational Codeforces Round 142 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1792/problem/C
// Memory Limit: 256 MB
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
#define pb push_back

using namespace std;

typedef vector<lli> vi;


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
	//returns the number of elements lesser than or equal to x int then subarray [l,..,r]
	int lessThanOrEqual(int l, int r, int x){
		if(l > r || low > x) return 0;
		if(high <= x) return r-l+1;
		int izq,der;
		izq = mapLeft[l-1];
		der = mapLeft[r];
		return left->lessThanOrEqual(izq+1,der,x) + right->lessThanOrEqual(l-izq,r-der,x);
	}
	//returns the k-th element in the range [l,r] if the subarray were sorted
	int kth(int l, int r, int k){
		if(l > r)//if no element exists
			return -1;
		if(low == high)
			return low;
		int lb = mapLeft[l - 1], rb = mapLeft[r];
		int inLeft = rb - lb;
		if(k <= inLeft)
			return left->kth(lb + 1, rb, k);
		else 
			return right->kth(l - lb, r - rb, k - inLeft);
	}
	//counts the elements in the range[l,r] such that its value is in the range [a,b]
	int elementsInRange(int l, int r, int a,int b){
		if(l > r || (a < low && b < low) || (a > high && b > high))
			return 0;
		if(a <= low && b >= high)
			return r - l + 1;
		int lb = mapLeft[l - 1], rb = mapLeft[r];
		return left->elementsInRange(lb + 1, rb, a, b) + right->elementsInRange(l - lb, r - rb, a, b);
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



void main_(){
	int n; cin>>n;
	vector<lli> nums(n);
	for(auto &x: nums) cin>>x;
	
	
	vector<lli> index(n+1);
	for(int i = 0; i < n; i++){
		auto num = nums[i];
		index[num] = i;
	}


	map<lli,lli> num_to_pair;
	vector< pair<lli,lli> > pairs;
	for(int i = 1; i <= n; i++){
		if(n-i+1 < i) break;
		num_to_pair[i] = i;
		num_to_pair[n-i+1] = i;
		pairs.push_back({i, n - i + 1});
	}

	vector<lli> for_wavelet;
	for(int i = 0; i < n; i++){
		auto num = nums[i];
		for_wavelet.push_back( num_to_pair[num]  );
	}


	WaveletTree *WT = new WaveletTree(all(for_wavelet), *min_element(all(for_wavelet)), *max_element(all(for_wavelet)));

	sort(all(pairs), [](pair<lli,lli> a, pair<lli,lli> b){
		return a.first > b.first;
	});


	


	int m = SZ(pairs);
	for(int i = 0; i < m; i++){
		auto u = pairs[i].first, v = pairs[i].second;
		auto index_l = index[u] + 1, index_r = index[v] + 1;

		if(u == v) continue;

		if(index_l > index_r){
			cout << u << endl;
			return;
		}

		// cout << u << " - " << v << " " << index_l << " " << index_r << " " << num_to_pair[u] << endl;

		int need = v - u - 1;
		int how_many = WT->elementsInRange(index_l+1, index_r-1, num_to_pair[u], m);
		if(how_many < need) {
			cout << u << endl;
			return ;
		}

	}

	
	cout << 0 << endl;
	
	
}


int main () {
	fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

