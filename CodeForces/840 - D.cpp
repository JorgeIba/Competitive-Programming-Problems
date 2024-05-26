#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int aleatorio(int a, int b){
	std::uniform_int_distribution<int> dist(a, b);
	return dist(rng);
}

const int ITER = 100, INF = 1e9, maxA = 3e5+100;
int fr_a[maxA], fr_idx[maxA], nums[maxA];

struct Query{
    const static int BLOCK = 350;
	int l, r, k, indx;
	bool operator<(const Query& q) const{
		if(l/BLOCK != q.l/BLOCK) return l/BLOCK < q.l/BLOCK;
		if(l/BLOCK & 1) return r < q.r;
		return r > q.r;
	}
};

void add(int i){
	fr_a[nums[i]]++;
}
void remove(int i){
	fr_a[nums[i]]--;
}
int getAns(int l, int r, int limit){
    int ans = INF;
    forr(i, 1, ITER){
        int idx = aleatorio(l, r);

        if(fr_a[nums[idx]] > limit)
            ans = min(ans, nums[idx]);
    }
    return ans;
}

vector<int> mosAlgo(vector<Query> Q){
    int n = SZ(Q);
	vector<int> ans(n);
	sort(all(Q));
	int L = 1;
	int R = 0;
	for(int i = 0; i < n; i++){
		Query q = Q[i];
        while(L > q.l) add(--L);
		while(R < q.r) add(++R);
		
        while(L < q.l) remove(L++);
		while(R > q.r) remove(R--);
		
		ans[q.indx] = getAns(q.l, q.r, q.k);
	}
	return ans;
}

int main () {
	fastIO();
	
    int n, q; cin>>n>>q;
    forr(i, 1, n) cin>>nums[i];

    vector<Query> queries(q);
    forn(i, q){
        int l, r, k; cin>>l>>r>>k;
        queries[i] = {l, r, (r-l+1)/k, i};
    }

    auto ans = mosAlgo(queries);

    for(auto x: ans) cout << (x == INF ? -1 : x) << endl;

	return 0;
}

