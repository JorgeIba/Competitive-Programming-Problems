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

struct WaveletTree{
	int lo, hi;
	WaveletTree *left, *right;
	vector<int> freq;
	vector<int> pref; //just use this if you want sums

	//queries indexed in base 1, complexity for all queries: O(log(max_element))
	//build from [from, to) with non-negative values in range [x, y]
	//you can use vector iterators or array pointers
	WaveletTree(vector<int>::iterator from, vector<int>::iterator to, int x, int y): lo(x), hi(y){
		if(from >= to) return;
		int m = (lo + hi) / 2;
		auto f = [m](int x){return x <= m;};
		freq.reserve(to - from + 1);
		freq.push_back(0);
		pref.reserve(to - from + 1);
		pref.push_back(0);
		for(auto it = from; it != to; ++it){
			freq.push_back(freq.back() + f(*it));
			pref.push_back(pref.back() + *it);
		}
		if(hi != lo){
			auto pivot = stable_partition(from, to, f);
			left = new WaveletTree(from, pivot, lo, m);
			right = new WaveletTree(pivot, to, m + 1, hi);
		}
	}

	//kth element in [l, r]
	int kth(int l, int r, int k){
		if(l > r) return 0;
		if(lo == hi) return lo;
		int lb = freq[l - 1], rb = freq[r];
		int inLeft = rb - lb;
		if(k <= inLeft) return left->kth(lb + 1, rb, k);
		else return right->kth(l - lb, r - rb, k - inLeft);
	}

	//number of elements less than or equal to k in [l, r]
	int lessThanOrEqual(int l, int r, int k){
		if(l > r || k < lo) return 0;
		if(hi <= k) return r - l + 1;
		int lb = freq[l - 1], rb = freq[r];
		return left->lessThanOrEqual(lb + 1, rb, k) + right->lessThanOrEqual(l - lb, r - rb, k);
	}

	//number of elements equal to k in [l, r]
	int equalTo(int l, int r, int k){
		if(l > r || k < lo || k > hi) return 0;
		if(lo == hi) return r - l + 1;
		int lb = freq[l - 1], rb = freq[r];
		int m = (lo + hi) / 2;
		if(k <= m) return left->equalTo(lb + 1, rb, k);
		else return right->equalTo(l - lb, r - rb, k);
	}

	//sum of elements less than or equal to k in [l, r]
	int sum(int l, int r, int k){
		if(l > r || k < lo) return 0;
		if(hi <= k) return pref[r] - pref[l - 1];
		int lb = freq[l - 1], rb = freq[r];
		return left->sum(lb + 1, rb, k) + right->sum(l - lb, r - rb, k);
	}
};

int main () {
	fastIO();
    lli y, n; cin>>y>>n;
    vector<int> years(y);
    for(auto &x: years) cin>>x;

    vector<int> clone_years = years;

    WaveletTree *WT = new WaveletTree(all(years), 0, 1e5 + 10);

    for(int i = 0; i<n; i++)
    {
        lli a, p, f; cin>>a>>p>>f;
        if( clone_years[a-1] >= p  )
        {
            cout << 0 << endl;
            continue;
        }
        cout << (f) - (WT->lessThanOrEqual(a+1, a+f, p-1)) << endl;
    }
	


	return 0;
}

