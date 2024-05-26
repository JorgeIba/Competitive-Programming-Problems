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



bool verify(vector<int> nums, vector<int> last, int k){
    int n = SZ(nums);
    int m = SZ(last);

    int how_many = n - m;
    if(how_many > k) return false;


    vector<int> values(n+1);
    forn(i, n){
        values[ nums[i] ] = i;
    }

    forn(i, m-1){
        if(values[ last[i] ] > values[ last[i+1] ]) return false;
    }

    return true;
}


void main_(){
    int n, m, k; cin>>n>>m>>k;

    vector<int> nums(n), last(m), lens(k);
    for(auto &x: nums) cin>>x;
    for(auto &x: last) cin>>x;
    for(auto &x: lens) cin>>x;
    
    if(!verify(nums, last, k)) {
        cout << "NO" << endl;
        return;
    }

    vector<bool> needed(n+1);
    forn(i, m) needed[last[i]] = true;

    vector<int> pos(n+1);
    for(int i = 0; i < n; i++) pos[nums[i]] = i;


    multiset<int> ms_lens(all(lens));
    set<int> indexes;

    Fenwick FT(n);

    for(int i = n; i >= 1; i--){
        if(needed[i]) {
            indexes.insert(pos[i]);
            continue;
        }

        auto itr_l = indexes.lower_bound(pos[i]);
        auto itr_r = indexes.lower_bound(pos[i]);

        int l, r;
        if(itr_l == indexes.begin()) {
            l = -1;
        } else {
            itr_l--;
            l = *itr_l;
        }

        if(itr_r == indexes.end()){
            r = n;
        } else {
            r = *itr_r;
        }

        l++;
        r--;

        if(l > r) {
            assert(false);
        }

        int needs = r - l + 1 - FT.query(l+1, r+1);
        FT.update(pos[i]+1, 1);

        auto itr_len = ms_lens.upper_bound(needs);
        if(itr_len == ms_lens.begin()) {
            cout << "NO" << endl;
            return;
        }

        itr_len--;
        ms_lens.erase(itr_len);
    }

    cout << "YES" << endl;
 
}


int main () {
	//fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

