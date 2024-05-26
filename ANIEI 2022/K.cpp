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
	vector<lli> freq;
	vector<lli> pref; 

	WaveletTree(vector<lli>::iterator from, vector<lli>::iterator to, lli x, lli y): lo(x), hi(y){
        if(from >= to) return;
        lli m = (lo + hi) / 2;
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

	int kth(int l, int r, int k){
        if(l > r) return 0;
        if(lo == hi) return lo;
        int lb = freq[l - 1], rb = freq[r];
        int inLeft = rb - lb;
        if(k <= inLeft) return left->kth(lb + 1, rb, k);
        else return right->kth(l - lb, r - rb, k - inLeft);
	}

	lli sum(int l, int r, int k){
        if(l > r || k < lo) return 0;
        if(hi <= k) return pref[r] - pref[l - 1];
        lli lb = freq[l - 1], rb = freq[r];
        return left->sum(lb + 1, rb, k) + right->sum(l - lb, r - rb, k);
	}
};


int main () {
	fastIO();

    lli n, t; cin>>n>>t;

    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    vector<lli> part(n+1);
    for(int i = 1; i <= n; i++) {
        part[i] = part[i-1] + nums[i-1];
    }

    auto getSum = [&](lli l, lli r) {
        return part[r] - part[l-1];
    };

    WaveletTree *WT = new WaveletTree(all(nums), *min_element(all(nums)), *max_element(all(nums)));

    
    // for(auto x: part) cout << x << " ";
    // cout << endl;

    

    while(t--) {
        int l, r, k; cin>>l>>r>>k;
        lli kth = WT->kth(l, r, k);
        lli totalSum = getSum(l, r);
        lli lowerSum = WT->sum(l, r, kth);


        cout << kth << " " << (totalSum - lowerSum) << endl;
    }

	return 0;
}

