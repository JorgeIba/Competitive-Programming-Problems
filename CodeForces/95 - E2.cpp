#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;


vector< bool > visited;

vector< vector<int> > adjList;


int dfs(int u, int p = -1){
    visited[u] = true;
    int sz = 1;
    for(auto v: adjList[u]){
        if(v == p || visited[v]) continue;
        sz += dfs(v);
    }
    return sz;
}



int main () {
	//fastIO();
	
    int n, m; cin>>n>>m;
    
    adjList.resize(n+1);

    for(int i = 0; i < m; i++){
        int u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    vector< int > sizes;
    visited.resize(n+1);
    for(int i = 1; i <= n; i++){
        if(!visited[i]){
            int sz = dfs(i);
            sizes.push_back(sz);
        }
    }



    map<lli, int> freqs;
    for(auto x: sizes) freqs[x]++;

    

    vector< pair<int,int> > C;
    for(auto [x, freq_x]: freqs){
        int curr = 1;
        while(freq_x) {
            int to_add = min(curr, freq_x);
            C.push_back({to_add * x, to_add});
            freq_x -= to_add;
            curr <<= 1;
        }
    }

    set< lli > lucky_numbers_set = {0};
    for(int idx = 0; idx <= 6; idx++){
        set<lli> new_numbers;
        for(auto x: lucky_numbers_set){
            new_numbers.insert(10*x + 4);
            new_numbers.insert(10*x + 7);
        }
        lucky_numbers_set.insert(all(new_numbers));
    }

    lucky_numbers_set.erase(0);

    const int INF = 1e9;
    int l = SZ(C);
    vector< int > dp(vector<int>(n+1, INF));

    dp[0] = 0;

    for(int i = 1; i <= l; i++) {
        int val = C[i-1].first;
        int weight = C[i-1].second;
        
        auto new_dp = dp;

        for(int sz = 0; sz <= n; sz++){
            if(sz - val < 0) continue;
            new_dp[sz] = min(new_dp[sz], dp[sz - val] + weight);
        }

        dp = new_dp;
    }


    vector<lli> lucky_numbers(all(lucky_numbers_set));

    int ans = INF;
    for(auto lucky: lucky_numbers) {
        if(lucky > n) break;

        ans = min(ans, dp[lucky]);
    }

    cout << (ans != INF ? ans - 1 : -1 ) << endl;

    






	return 0;
}

