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

template<typename T>
struct SparseTable{
    vector< vector<T> > ST;
    vector<int> logs;
    int K, N;

    SparseTable(vector<T> &arr) {
        N = arr.size();
        K = log2(N) + 2;
        ST.assign(K+1, vector<T>(N));
        logs.assign(N + 1, 0);
        for(int i = 2; i <= N; i++)
            logs[i] = logs[i>>1] + 1;
        for(int i = 0; i < N; i++)
            ST[0][i] = arr[i];
        for(int j = 1; j <= K; j++)
            for(int i = 0; i + (1 << j) <= N; i++)
                ST[j][i] = max(ST[j-1][i], ST[j-1][i + (1 << (j-1))]);
    }

    T maximal(int l, int r) {
        int j = logs[r-l+1];
        return max(ST[j][l], ST[j][r - (1 << j) + 1]);
    }
};


struct Query{
    const static int BLOCK = /*alaneos*/777;
	int l, r, indx;
	bool operator<(const Query& q) const{
		if(l/BLOCK != q.l/BLOCK) return l/BLOCK < q.l/BLOCK;
		if(l/BLOCK & 1) return r < q.r;
		return r > q.r;
	}
};


const int MAXN = 5e5 + 1000;
const int SZ_BLOCK = /*alaneos*/777;
// int nums[MAXN];
map<int, vector<int> > pos;
int connectedLeft[MAXN], connectedRight[MAXN];
int nextLeft[MAXN], nextRight[MAXN];
int sizes[MAXN];
int in_block[MAXN / SZ_BLOCK + 2*SZ_BLOCK];

int n, m; 


inline void update_sz(int sizee, int x) {
    if(!sizee) return;
    sizes[sizee] += x;
    in_block[sizee / SZ_BLOCK] += x;
}


inline void addLeft(int i, int R){
    int next = nextRight[i];
    connectedRight[i] = i;

    if(next > R || next == -1) return;

    int next_after = connectedRight[next];
    connectedRight[next] = connectedLeft[next] = next;
    connectedRight[i] = next_after;
    connectedLeft[next_after] = i;

    int new_size = next_after - i;
    int old_size = next_after - next;
    update_sz(new_size, 1);
    update_sz(old_size, -1);
}


inline void addRight(int i, int L){
    int next = nextLeft[i];
    connectedLeft[i] = i;

    if(next < L || next == -1) return;

    int next_after = connectedLeft[next];
    connectedRight[next] = connectedLeft[next] = next;
    connectedLeft[i] = next_after;
    connectedRight[next_after] = i;

    int new_size = i - next_after;
    int old_size = next - next_after;
    update_sz(new_size, 1);
    update_sz(old_size, -1);
}

inline void removeLeft(int i, int R){
    int next = nextRight[i];

    if(next > R || next == -1) return;

    int conn_right = connectedRight[i];

    connectedRight[i] = connectedLeft[i] = i;
    connectedRight[next] = conn_right;
    connectedLeft[conn_right] = next;

    int old_size = conn_right - i;
    int new_size = conn_right - next;
    update_sz(new_size, 1);
    update_sz(old_size, -1);
}

inline void removeRight(int i, int L){
	int next = nextLeft[i];

    if(next < L || next == -1) return;

    int conn_left = connectedLeft[i];

    connectedRight[i] = connectedLeft[i] = i;
    connectedLeft[next] = conn_left;
    connectedRight[conn_left] = next;

    int old_size = i - conn_left;
    int new_size = next - conn_left;

    update_sz(new_size, 1);
    update_sz(old_size, -1);
}

inline int getAns(int L, int R){

    for(int block = MAXN/SZ_BLOCK; block >= 0; block--) {
        if(in_block[block]) {
            for(int j = (block+1) * SZ_BLOCK - 1; j >= 1 ; j--) {
                if(sizes[j])
                    return j;
            }
        }
    }

    return 0;
}


inline vector<int> mosAlgo(vector<Query> Q){
    int n = SZ(Q);
	vector<int> ans(n);
	sort(all(Q));
	int L = 0;
	int R = -1;
	for(int i = 0; i < n; i++){
		Query q = Q[i];
        while(L > q.l) addLeft(--L, R);
		while(R < q.r) addRight(++R, L);
		
        while(L < q.l) removeLeft(L++, R);
		while(R > q.r) removeRight(R--, L);
		
		ans[q.indx] = getAns(L, R);
	}
	return ans;
}


int main () {
	//fastIO();
	
    cin>>n>>m;

    vector<int> nums(n);    
    for(auto &x: nums) cin>>x;

    vector< Query > queries(m);
    forn(i, m) {
        int l, r; cin>>l>>r; l--, r--;
        queries[i].l = l;
        queries[i].r = r;
        queries[i].indx = i;
    }


    for(int i = 0; i < n; i++) {
        auto num = nums[i];
        pos[num].push_back(i);
    }

    SparseTable<int> *ST = new SparseTable<int>(nums);

    memset(nextLeft,  -1, sizeof(nextLeft));
    memset(nextRight, -1, sizeof(nextRight));
    iota(connectedLeft,  connectedLeft + MAXN, 0);
    iota(connectedRight, connectedRight + MAXN, 0);

    for(auto [x, poss]: pos) {
        int t = SZ(poss);
        for(int i = 0; i < t-1; i++) {
            int curr = poss[i];
            int next = poss[i+1];
            int maxi = ST->maximal(curr, next);
            if(maxi <= x) {
                nextRight[curr] = next;
            }
        }

        for(int i = 1; i < t; i++) {
            int curr = poss[i];
            int next = poss[i-1];
            int maxi = ST->maximal(next, curr);
            if(maxi <= x) {
                nextLeft[curr] = next;
            }
        }
    }

    auto ans = mosAlgo(queries);
    for(auto x: ans) cout << x << endl;

	return 0;
}

