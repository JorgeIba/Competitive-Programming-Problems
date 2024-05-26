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
	vector<vector<T>> ST;
	vector<int> logs;
	int K, N;

    SparseTable(){}

	SparseTable(vector<T> & arr){
		N = arr.size();
		K = log2(N) + 2;
		ST.assign(K + 1, vector<T>(N));
		logs.assign(N + 1, 0);
		for(int i = 2; i <= N; ++i)
			logs[i] = logs[i >> 1] + 1;
		for(int i = 0; i < N; ++i)
			ST[0][i] = arr[i];
		for(int j = 1; j <= K; ++j)
			for(int i = 0; i + (1 << j) <= N; ++i)
				ST[j][i] = min(ST[j - 1][i], ST[j - 1][i + (1 << (j - 1))]);
	}

	T minimal(int l, int r){ 
		int j = logs[r - l + 1];
		return min(ST[j][l], ST[j][r - (1 << j) + 1]);
	}
};


const int MAXQ = 300 + 10;
const lli INF = 1e15;
lli dp[MAXQ][MAXQ][MAXQ];


int main () {
	//fastIO();

    int n, q; cin>>n>>q;
    vector< int > A(q+1);
    forr(i, 1, q) cin>>A[i];

    vector< vector<lli> > costs(3, vector<lli>(q+1));
    vector< vector<bool> > on(3, vector<bool>(q+1));
    vector< array<int,2> > queries(q+1, {-1,-1});
    on[0][0] = on[1][0] = on[2][0] = true;
    costs[0][0] = costs[1][0] = costs[2][0] = INF;
    queries[0] = {1, 1};

    forr(i, 1, q){
        int t; cin>>t;

        forn(j, 3)
            on[j][i] = on[j][i-1];

        if(t == 1){
            int x, y; cin>>x>>y;
            queries[i] = {x, y};
        } else {
            int p; cin>>p; p--;
            on[p][i] = !on[p][i];
        }

        forn(j, 3){
            costs[j][i] = (on[j][i] ? A[i] : INF);
        }
    }


    vector< int > next_query(q+2, -1);
    int last = -1;
    for(int i = q; i >= 0; i--){
        if(queries[i][0] != -1) last = i;
        next_query[i] = last;
    }

    memset(dp, -1, sizeof(dp));

    vector< SparseTable<lli> > STs(3);
    forn(i, 3)
        STs[i] = SparseTable<lli>(costs[i]);

    auto g = [&](int last_q, int next_q, int door){
        lli mn = STs[door].minimal(last_q, next_q);
        if(mn == INF) return INF;
        if(!on[door][next_q]) return INF;
        assert(queries[last_q][0] != -1);
        assert(queries[next_q][0] != -1);

        lli cost = abs(queries[last_q][1] - queries[next_q][0]) * mn + abs(queries[next_q][0] - queries[next_q][1]) * costs[door][next_q];
        return cost;
    };


    auto f = [&](const auto &f, int i, int j, int k) -> lli {
        int last_query = max({i, j, k});
        int idx_next = next_query[last_query+1];
        if(idx_next == -1) return 0;

        lli &ans = dp[i][j][k];
        if(ans != -1) return ans;

        return ans = min({
            f(f, idx_next, j, k) + g(i, idx_next, 0),
            f(f, i, idx_next, k) + g(j, idx_next, 1),
            f(f, i, j, idx_next) + g(k, idx_next, 2)
        });
    };

    cout << f(f, 0, 0, 0) << endl;


	return 0;
}

