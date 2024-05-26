#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

const int INF = 1e9;

vector<int> get_ans(const vector<pair<int,int>> &C, int total_sum, int m) {
    int n = SZ(C);
    vector< vector<int> > dp(n, vector<int>(m+1, INF));

    dp[0][total_sum] = 0;
    for(int i = 1; i < n; i++){
        auto diff = C[i].first;
        auto weight = C[i].second;

        for(int sum = 0; sum <= m; sum++) 
            dp[i][sum] = dp[i-1][sum];
            
        for(int sum = 0; sum <= m; sum++){
            if(sum + diff < 0) continue;
            if(dp[i-1][sum] == INF) continue;

            dp[i][sum + diff] = min(dp[i][sum+diff], dp[i-1][sum] + weight);
        }
    }

    return dp[n-1];
}


int main () {
	fastIO();

    int n, m; cin>>n>>m;
    vector<int> A(n+1), B(n+1);

    for(int i = 1; i <= n; i++) cin>>A[i]>>B[i];

    lli total_sum = 0;
    vector<int> C(n+1);
    for(int i = 1; i <= n; i++) {
        C[i] = B[i] - A[i];
        total_sum += A[i];
    }


    map<int,int> fr;
    for(int i = 1; i <= n; i++)
        fr[C[i]]++;


    vector<pair<int,int>> C_op = {{0,0}};
    for(auto [x, fr_x]: fr) {
        
        for(int w = 0; (1<<w) <= fr_x; w++){
            C_op.push_back({ (1<<w) * x, (1<<w) });
            fr_x -= (1 << w);
        }
        if(fr_x)
            C_op.push_back({fr_x*x, fr_x});
    }

    
    auto ans = get_ans(C_op, total_sum, m);
    for(auto x: ans) cout << (x == INF ? -1 : x) << endl;
    

	return 0;
}

