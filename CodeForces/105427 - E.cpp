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


const int MAXS = 10000 + 5;
const int MAXN = 1000 + 5;

const lli INF = 1e18;

template<typename T>
struct SparseTable{
	vector<vector<T>> ST;
	vector<int> logs;
	int K, N;

	SparseTable(vector<T> & arr) {
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

	T query(int l, int r){
        if(l >= N) return {INF, INF};
        if(r >= N) r = N-1;
        
		int j = logs[r - l + 1];
		return min(ST[j][l], ST[j][r - (1 << j) + 1]);
	}
};


int main () {
	fastIO();

    int n; cin>>n;
    vector< array<lli,2> > comps(n);
    for(auto &[f, t]: comps)
        cin>>f>>t;

    sort(all(comps), [&](auto a, auto b){
        return a[1] > b[1];
    });

    
    auto get_k = [&](int idx) {
        int j = -idx;
        return j / 2;
    };

    vector<lli> dp_old(MAXS, 0);
    for(int i = n-1; i >= 0; i--) {
        auto [f_i, t_i] = comps[i];

        vector<lli> dp_new(MAXS, INF);
        vector< tuple<lli,int> > best_odd(MAXS, {INF, INF});
        vector< tuple<lli,int> > best_even(MAXS, {INF, INF});

        for(int j = MAXS-1; j >= 0; j--) {
            if(j & 1)
                best_odd[j] = {dp_old[j] - t_i * get_k(j), j};
            else
                best_even[j] = {dp_old[j] - t_i * get_k(j), j};
        }

        SparseTable< tuple<lli,int> > ST_odd(best_odd), ST_even(best_even);
        for(int j = 0; j < MAXS; j++) {
            int k = min(int(f_i), j);
            int l = j + f_i - 2*k, r = j + f_i;
            lli ans_score, ans_j;

            if(l & 1)
                tie(ans_score, ans_j) = ST_odd.query(l, r);
            else
                tie(ans_score, ans_j) = ST_even.query(l, r);
            
            int ans_k = get_k(ans_j);
            int should_be = ans_k - get_k(r);
            dp_new[j] = t_i * f_i + ans_score + t_i * (ans_k - should_be);
        }


        swap(dp_new, dp_old);
    }
    cout << dp_old[0] << endl;



	return 0;
}

