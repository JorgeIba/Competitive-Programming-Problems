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

const int MAXN = 1e5 + 5;
int frq[MAXN+10];
int cnt[MAXN+10];
int nums[MAXN+10], nums_update[MAXN+10];
int nextt[MAXN+10], prevv[MAXN+10];
const static int BLOCK = 3569;

struct Query{    
	int l, r, k, t, indx;
	bool operator<(const Query& q) const{
		if(l/BLOCK != q.l/BLOCK) return l/BLOCK < q.l/BLOCK;
		if(r/BLOCK != q.r/BLOCK) return r/BLOCK < q.r/BLOCK;
		return t < q.t;
	}
};

struct Update{
    int pos, oldVal, newVal;
};

inline void insert(int left, int num, int right){
    nextt[left] = num;
    prevv[num] = left;
    nextt[num] = right;
    prevv[right] = num;
}

inline void erase(int left, int num, int right){
    nextt[left] = right;
    prevv[right] = left;

    prevv[num] = 0;
    nextt[num] = MAXN;
}

inline void add(int i){
	int val = nums[i];

    int old_frq = frq[val];
    int new_frq = ++frq[val];

    cnt[new_frq]++;
    if(cnt[new_frq] == 1){
        insert(old_frq, new_frq, nextt[old_frq]);
    }

    cnt[old_frq]--;
    if(cnt[old_frq] == 0){
        erase(prevv[old_frq], old_frq, nextt[old_frq]);
    }
}

inline void remove(int i){
	int val = nums[i];

    int old_frq = frq[val];
    int new_frq = --frq[val];

    cnt[new_frq]++;
    if(cnt[new_frq] == 1){
        insert(prevv[old_frq], new_frq, old_frq);
    }

    cnt[old_frq]--;
    if(cnt[old_frq] == 0){
        erase(prevv[old_frq], old_frq, nextt[old_frq]);
    }
}

inline void doUpdate(const Update &U, int l, int r){
    auto [idx, oldVal, newVal] = U;
    bool inside = l <= idx && idx <= r;
    assert(nums[idx] == oldVal);
    
    if(inside)
        remove(idx);

    nums[idx] = newVal;

    if(inside)
        add(idx);
}

inline void undoUpdate(const Update &U, int l, int r){
    auto [idx, oldVal, newVal] = U;
    bool inside = l <= idx && idx <= r;
    assert(nums[idx] == newVal);

    if(inside)
        remove(idx);

    nums[idx] = oldVal;

    if(inside)
        add(idx);
}


inline int getAns(int k){
    int l = nextt[0], r = 0;
    int acum = 0;
    int ans = MAXN;

    while(r < MAXN){
        while(acum < k && nextt[r] != MAXN) {
            r = nextt[r];
            acum += cnt[r];
        }

        if(acum >= k) {
            ans = min(ans, r - l);
        } 
        acum -= cnt[l];
        l = nextt[l];
        if(l > r) r = nextt[r];
    }

    return ans == MAXN ? -1 : ans;
}

inline vector<int> mosAlgo(vector<Query> Q, const vector<Update> &U){
    int n = SZ(Q);
	vector<int> ans(n);
	sort(all(Q));
	int L = 0; 
	int R = -1;
    int timeU = 0;
	for(int i = 0; i < n; i++){
		Query q = Q[i];

        while(L > q.l) add(--L);
		while(R < q.r) add(++R);
		
        while(L < q.l) remove(L++);
		while(R > q.r) remove(R--);

        while(timeU < q.t){
            doUpdate(U[timeU], q.l, q.r);
            timeU++;
        }

        while(timeU > q.t){
            timeU--;
            undoUpdate(U[timeU], q.l, q.r);
        }

		ans[q.indx] = getAns(q.k);        
	}
	return ans;
}


int main () {
	fastIO();
	
    int n, q; cin>>n>>q;

    forn(i, n){
        cin>>nums[i];
        nums_update[i] = nums[i];
    }

    forn(i, MAXN){
        nextt[i] = MAXN;
    }

    vector< Query > queries;
    vector< Update > updates;

    int timee = 0;
    forn(i, q){
        int t; cin>>t;
        if( t == 1 ) {
            int l, r, k; cin>>l>>r>>k; l--, r--;
            queries.push_back({l, r, k, timee, SZ(queries)});
        } else {
            int p, x; cin>>p>>x; p--;

            updates.push_back({p, nums_update[p], x});
            nums_update[p] = x;

            timee++;
        }
    }

    auto ans = mosAlgo(queries, updates);

    for(auto x: ans) cout << x << endl;


	return 0;
}

