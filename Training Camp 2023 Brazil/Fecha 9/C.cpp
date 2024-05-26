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

typedef pair<lli,lli> pairi;

vector< vector< pairi > > adjList;

const int maxN = 1e5+1000;
lli dp[maxN][2];


lli f(int u, bool from_top, int p = -1){

    if(SZ(adjList[u]) == 1) return 0;

    lli &ans_dp = dp[u][from_top];
    if(ans_dp != -1) return ans_dp;


    vector<lli> vals;
    lli total_sum = 0;
    for(auto [v, w]: adjList[u]){
        if(v == p) continue;

        lli yes = f(v, true, u) + w;
        lli no = f(v, false, u); 

        total_sum += no;
        vals.push_back(yes - no);
    }

    sort(all(vals), greater<lli>());

    int start = 0;
    if(from_top) {
        total_sum += vals[0];
        start = 1;
    }

    int m = SZ(vals);

    lli ans = total_sum;
    for(int i = start; i+1 < m; i += 2){
        lli new_sum = total_sum + vals[i] + vals[i+1];
        ans = max(ans, new_sum);
        total_sum += vals[i] + vals[i+1];
    }   

    return ans_dp = ans;
}



int main () {
	fastIO();
	
    int n; cin>>n;

    adjList.resize(n+1);

    forr(i, 1, n-1) {
        int u, v, w; cin>>u>>v>>w;
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w});
    }


    if(n == 2){
        cout << adjList[1][0].second << endl;
        return 0;
    }

    int root = 1;
    if(SZ(adjList[1]) == 1)
        root = adjList[1][0].first;

    assert(SZ(adjList[root]) > 1);
    memset(dp, -1, sizeof(dp));

    auto ans = f(root, false);

    cout << ans << endl;

	return 0;
}

