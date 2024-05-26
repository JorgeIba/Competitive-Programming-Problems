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


int k;
const int maxN = 1e5+1000;

int prefs[maxN];
int fr_prefs[(1LL << 20)];

struct Query{
    const static int BLOCK = 300;
	int l, r, indx;
	bool operator<(const Query& q) const{
		if(l/BLOCK != q.l/BLOCK) return l/BLOCK < q.l/BLOCK;
		if(l/BLOCK & 1) return r < q.r;
		return r > q.r;
	}
};

lli total_ans = 0;
void add(int i){
	
    total_ans += (fr_prefs[  k ^  prefs[i]   ]);   
    fr_prefs[prefs[i]]++;
}

void remove(int i){
    fr_prefs[prefs[i]]--;
    total_ans -= (fr_prefs[  k ^  prefs[i]   ]);
    
}

lli getAns(){
	return total_ans;
}

vector<lli> mosAlgo(vector<Query> Q){
    int n = SZ(Q);
	vector<lli> ans(n);
	sort(all(Q));
	int L = 1; 
	int R = 0;
	for(int i = 0; i < n; i++){
		Query q = Q[i];
        while(L > q.l) add(--L);
		while(R < q.r) add(++R);
		
        while(L < q.l) remove(L++);
		while(R > q.r) remove(R--);
		
		ans[q.indx] = getAns();
	}
	return ans;
}


int main () {
	//fastIO();

    int n, m; cin>>n>>m>>k;

    vector<int> nums(n+1);
    forr(i, 1, n) cin>>nums[i];

    forr(i, 1, n) 
        prefs[i] = prefs[i-1] ^ nums[i];
    
    vector< Query > queries(m);
    forn(i, m){
        int l, r; cin>>l>>r;
        queries[i].l = l-1;
        queries[i].r = r;
        queries[i].indx = i;
    }


    auto ans = mosAlgo(queries);

    for(auto x: ans) cout << x << endl;  



	return 0;
}

