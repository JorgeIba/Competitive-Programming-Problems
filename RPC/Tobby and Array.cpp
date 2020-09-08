#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(lli i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define SZ(s) lli(s.size())

using namespace std;

struct WaveletTree{
	lli lo, hi;
	WaveletTree *left, *right;
	vector<lli> freq;

	//queries indexed in base 1, complexity for all queries: O(log(max_element))
	//build from [from, to) with non-negative values in range [x, y]
	//you can use vector iterators or array pointers
	WaveletTree(vector<lli>::iterator from, vector<lli>::iterator to, lli x, lli y): lo(x), hi(y){
		if(from >= to) return;
		lli m = (lo + hi) / 2;
		auto f = [m](lli x){return x <= m;};
		freq.reserve(to - from + 1);
		freq.push_back(0);
		for(auto it = from; it != to; ++it){
			freq.push_back(freq.back() + f(*it));
		}
		if(hi != lo){
			auto pivot = stable_partition(from, to, f);
			left = new WaveletTree(from, pivot, lo, m);
			right = new WaveletTree(pivot, to, m + 1, hi);
		}
	}

	//kth element in [l, r]
	lli kth(lli l, lli r, lli k){
		if(l > r) return -1;
		if(lo == hi) return lo;
		lli lb = freq[l - 1], rb = freq[r];
		lli inLeft = rb - lb;
		if(k <= inLeft) return left->kth(lb + 1, rb, k);
		else return right->kth(l - lb, r - rb, k - inLeft);
	}
};

void solve(lli n, lli q)
{
    vector< lli > nums(n);
    set<lli> uniqueN;
    for(auto &x: nums) cin>>x, uniqueN.insert(x);
    map<lli,lli> cod;
    map<lli,lli> decod;

    lli id = 1;
    for(auto x: uniqueN)
    {
        cod[x] = id;
        decod[id++] = x;
    }
    for(int i = 0; i<n; i++)
    {
        nums[i] = cod[nums[i]];
    }

    WaveletTree w(all(nums), *min_element(all(nums)), *max_element(all(nums)));
    while(q--)
    {
        lli l, r, k; cin>>l>>r>>k;
        //assert(k>=1 && k<=r-l+1);
        lli res = w.kth(l, r, k);
        assert(res != -1);
        cout << decod[w.kth(l,r,k)] << endl;
    }
}


int main () {
	fastIO();
    lli n, q;
    while(cin>>n>>q){
    //while(cin>>n>>q){
        solve(n, q);
    } 
	return 0;
}