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


const int INF = 1e9;


struct WaveletTree{
	int lo, hi;
	WaveletTree *left, *right;
	vector<int> freq;

	WaveletTree(vector<int>::iterator from, vector<int>::iterator to, int x, int y): lo(x), hi(y){
		if(from >= to) return;
		int m = (lo + hi) / 2;
		auto f = [m](int x){return x <= m;};
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

    int minFreqK(int l, int r, int k){
        if(l > r) return INF;
        if(lo == hi) return lo;

        int lb = freq[l-1], rb = freq[r];
        int inLeft = rb-lb;
        int inRight = (r-l+1) - inLeft;
        int mini = INF;

        if(inLeft > k) {
            mini = min(mini, left->minFreqK(lb+1, rb, k));
        }
        if(inRight > k){
            mini = min(mini, right->minFreqK(l-lb, r-rb, k));
        }
        return mini;
    }

};


int main () {
	fastIO();
	
    int n, q; cin>>n>>q;

    vector<int> nums(n);
    for(auto &x: nums) cin>>x;


    auto aux = nums;

    WaveletTree WT(all(aux), *min_element(all(aux)), *max_element(all(aux)));

    while(q--){
        int l, r, k; cin>>l>>r>>k;

        auto ans = WT.minFreqK(l, r, (r-l+1)/k);

        cout << (ans != INF ? ans : -1) << endl;
    }

	return 0;
}

