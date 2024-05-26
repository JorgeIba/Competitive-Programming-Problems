#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;

const int INF = 1e9;

template <typename T,typename S>
struct SegmentTreeItLazy{
	T neutro = INF, neutro_lazy = INF;
	int size, height;
	vector<T> st, delUp;
	vector<bool> upd;

	SegmentTreeItLazy(int n, T val = 0){
		st.resize(2*n);
        size = n;
        delUp.resize(n, neutro_lazy);
		upd.resize(n);
        height = sizeof(int) * 8 - __builtin_clz(size);

        fill(all(st), val);
		build();
	}
	T merge(T a, T b){
		return min(a, b);
	}
	void apply(int i, T val, int k){
		st[i] = min(st[i], val);
		if (i < size) delUp[i] = min(delUp[i], val), upd[i] = 1;
	}
	void calc(int i){
		if (!upd[i]) st[i] = merge(st[i << 1], st[i << 1 | 1]);
	}
	void build(){
		for(int i = size - 1; i; i--) calc(i);
	}
	void build(int p) {
		while (p > 1) p >>= 1, calc(p);
	}
	void push(int p) {
		for (int s = height, k = 1 << (height - 1); s; s--, k >>= 1){
			int i = p >> s;
			if (upd[i]){
				apply(i << 1, delUp[i], k);
				apply(i << 1 | 1, delUp[i], k);
				upd[i] = 0, delUp[i] = neutro_lazy;
			}
		}
	}
	void update(int l, int r, T val){
		push(l += size), push(r += size);
		int ll = l, rr = r, k = 1;
		for (; l <= r; l >>= 1, r >>= 1, k <<= 1) {
			if (l & 1) apply(l++, val, k);
			if (~r & 1) apply(r--, val, k);
		}
		build(ll), build(rr);
	}
	T query(int l, int r){
        T ansL = neutro;
        T ansR = neutro;
        push(l += size);
        push(r += size);
        for (; l <= r; l >>= 1, r >>= 1){
                if (l & 1) ansL = merge(ansL, st[l++]);
                if (~r & 1) ansR = merge(st[r--], ansR);
        }
        return merge(ansL, ansR);
    }
};

vector<int> manacher(const string &s){
    int n = 2 * s.length();
    vector<int> rad(n);

    for (int i = 0, j = 0, k; i < n; i += k, j = max(j - k, 0)) {
        for (; i >= j && i + j + 1 < n 
                && s[(i - j) / 2] == s[(i + j + 1) / 2]; ++j);
        rad[i] = j;
        for (k = 1; i >= k && rad[i] >= k && rad[i - k] != rad[i] - k; ++k)
            rad[i + k] = min(rad[i - k], rad[i] - k);
    }

    return rad;
}

void main_(){
    int n; cin>>n;

    string s; cin>>s;
    auto man = manacher(s);

    SegmentTreeItLazy<int, int> ST(n, INF);
    for(int i = 1; i < SZ(man); i += 2){
        if(!man[i]) continue;

        int idx_l = (i+1 - man[i])/2;
        int idx_r = idx_l + man[i]/2 - 1;
        ST.update(idx_l, idx_r, i);
    }

    vector<int> nextt(n);
    for(int i = 0; i < n; i++){
        nextt[i] = ST.query(i, i);
    }

    vector<lli> dp(n, -1);
    auto f = [&](const auto &f, int idx){
        if(idx >= n) return 0LL;
        if(nextt[idx] == INF) return 0LL;

        lli &ans = dp[idx];
        if(ans != -1) return ans;

        int next_idx = (nextt[idx] - idx) + 1;
        return ans = 1 + f(f, next_idx);
    };
    
    lli ans = 0;
    for(int i = 0; i < n; i++){
        ans += f(f, i);
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

