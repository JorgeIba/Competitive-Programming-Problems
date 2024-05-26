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


//build on O(n log n), queries in O(1) for any operation
template<typename T>
struct DisjointSparseTable{
	vector<vector<T>> left, right;
	int K, N;
    lli p;

	DisjointSparseTable(lli p, vector<T> & arr): p(p){
		N = arr.size();
		K = log2(N) + 2;
		left.assign(K + 1, vector<T>(N));
		right.assign(K + 1, vector<T>(N));
		for(int j = 0; (1 << j) <= N; ++j){
			int mask = (1 << j) - 1;
			T acum = 1; //neutral element of your operation
			for(int i = 0; i < N; ++i){
				acum = acum*arr[i] % p; //your operation
				left[j][i] = acum;
				if((i & mask) == mask) acum = 1; //neutral element of your operation
			}
			acum = 1; //neutral element of your operation
			for(int i = N-1; i >= 0; --i){
				acum = acum*arr[i] % p; //your operation
				right[j][i] = acum;
				if((i & mask) == 0) acum = 1; //neutral element of your operation
			}
		}
	}

	T query(int l, int r){
		if(l == r) return left[0][l];
		int i = 31 - __builtin_clz(l^r);
		return left[i][r]*right[i][l] % p; //your operation
	}
};



int main () {
	fastIO();

    lli t; cin>>t;

    while(t--) {
        lli n, p, q; cin>>n>>p>>q;
        vector<lli> nums(n);
        for(auto &x: nums) cin>>x;

        DisjointSparseTable<lli> *ST = new DisjointSparseTable<lli>(p, nums);
        
        lli szB = q/64+2;
        vector<lli> B(szB);
        for(auto &x: B) cin>>x;

        lli x = 0;
        pair<lli,lli> last;
        for(int i = 0; i < q; i++) {
            lli l, r;
            if(i % 64 == 0) {
                l = (B[i/64] + x) % n;
                r = (B[i/64+1] + x) % n;
            } else {
                l = (last.first+x) % n;
                r = (last.second+x) % n;
            }

            if(l > r) swap(l,r);

            lli ans = ST->query(l, r);

            // cout << l << " " << r << " " << endl;

            x = (ans+1) % p;
            last = {l,r};
        }
        cout << x << endl;
        
    }

	return 0;
}

