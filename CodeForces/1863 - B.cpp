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

// 1-indexed
struct Fenwick {
    int n;
    vector<long long> tree;

    Fenwick(int _n): n(_n), tree(n+1, 0) { }

    void update(int idx, long long val) {
        for (; idx <= n ; idx += idx & -idx) {
            tree[idx] += val;
        }
    }

    long long query(int idx) {
        long long ret = 0;
        for(; idx > 0 ; idx -= idx & -idx){
            ret += tree[idx];
        }
        return ret;
    }

    long long query(int x, int y) {
        return query(y) - query(x-1);
    }
};


void main_(){
    int n; cin>>n;
    vector<int> nums(n);
    for(auto &x: nums) cin>>x;

    vector<int> fr(n+1);

    int ans = 0;
    for(int i = n-1; i >= 0; i--){
        auto x = nums[i];
        ans += (fr[x-1] == 1);

        fr[x]++;
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

