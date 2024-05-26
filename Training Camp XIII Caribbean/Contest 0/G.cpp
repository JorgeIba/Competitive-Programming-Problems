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

// Offline queries. Runs on O(n*sqrt(n))
struct Query{
    const static int BLOCK = 300;
	int l, r, indx;
    Query(){}
    Query(int l, int r, int idx): l(l), r(r), indx(idx) {}
	bool operator<(const Query& q) const{
		if(l/BLOCK != q.l/BLOCK) return l/BLOCK < q.l/BLOCK;
		if(l/BLOCK & 1) return r < q.r;
		return r > q.r;
	}
};


const lli MAXA = 1e6+10;
lli fr[MAXA];

lli powerful = 0;

// Change the 2 functions below deppending on the problem
void add(lli i){
    lli F = fr[i];
    powerful = powerful + 2 * F * i + i;
    fr[i]++;
}
void remove(lli i){
	lli F = fr[i];
    powerful = powerful - 2 * F * i + i;
    fr[i]--;
}

lli getAns(){
	return powerful;
}
// Be careful of return type
vector<lli> mosAlgo(const vector<int> &nums, vector<Query> Q){
    int n = SZ(Q);
	vector<lli> ans(n);
	sort(all(Q));
	int L = 0; // If 1-indexed L = 1, R = 0
	int R = -1;
	for(int i = 0; i < n; i++){
		Query q = Q[i];
        while(L > q.l) add(nums[--L]);
		while(R < q.r) add(nums[++R]);
		
        while(L < q.l) remove(nums[L++]);
		while(R > q.r) remove(nums[R--]);
		
		ans[q.indx] = getAns();
	}
	return ans;
}



int main () {
	fastIO();
    
    int n, t; cin>>n>>t;

    vector<int> nums(n);
    for(auto &x: nums) cin>>x;

    vector<Query> queries(t);
    forn(i, t){
        int l, r; cin>>l>>r; l--, r--;
        queries[i] = {l, r, i};
    }

    auto ans = mosAlgo(nums, queries);

    for(auto x: ans) cout << x << endl;
    

	return 0;
}

