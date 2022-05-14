#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;

const lli maxN = 3e3 +10;
const lli INF = 2e9;


template<typename T>
struct SparseTable{
    int N, maxLevel;
    vector<vector<T>> table;

    SparseTable(vector<T> &init) {
        N = init.size(); maxLevel = log2(N) + 1;
        table.assign(maxLevel+1, vector<T>(N));

        for(int i = 0; i<N; i++) table[0][i] = init[i];
        for(int lvl = 1; lvl <= maxLevel; lvl++){
            for(int i = 0; i<N; i++){
                int idx_half = i + (1 << (lvl-1));
                if(idx_half >= N) continue;
                table[lvl][i] = operation(table[lvl-1][i], table[lvl-1][idx_half]);
            }
        }
    }

    // 0-indexed
    T query(lli l, lli r) {
        lli idx = l, sizee = r-l+1, pot = 0;
        T ans = neutro();

        while(sizee){
            if(sizee & 1){
                ans = operation(ans, table[pot][idx]);
                idx += (1 << pot);
            } 
            pot++;
            sizee>>=1;
        }

        return ans;
    }

    T operation(T a, T b){ return max(a, b); }
    T neutro() { return -INF; }
};


int main () {
	// fastIO();
    lli n; cin>>n;
    
    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;


    vector< vector<lli> > dp(n+1, vector<lli>(n+1, -INF));

    // dp[sq][limit_v] = la cantidad máxima de puntos en sq con limite de velocidad limit_v
    // ans = max(dp[n-1][v]) entre todos los v's
    // dp[0][v] = nums[0] para todo v

    for(int i = 1; i<=n; i++) dp[0][i] = nums[0];

    for(int sq = 1; sq <= n-1; sq++)
    {
        vector<lli> to_get_max(sq+1);
        for(int v = 1; v <= sq; v++)
        {
            to_get_max[v] = dp[sq-v][v];
        }
        
        SparseTable<lli> *ST = new SparseTable<lli>(to_get_max);


        for(int v = 1; v <= n-1; v++)
        {    
            lli limit_l = v, limit_r = sq;
            if( limit_l > limit_r) continue;
            dp[sq][v] = ST->query(limit_l, limit_r) + nums[sq];
        }
        
        
    }

    lli ans = -INF;
    for(int v = 1; v<=n-1; v++) ans = max(ans, dp[n-1][v]);

    cout << ans << endl;

	return 0;
}

