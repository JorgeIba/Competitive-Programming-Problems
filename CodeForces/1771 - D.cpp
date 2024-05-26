#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

vector< vector<int> > adjList;
vector< vector<int> > next_node;
string s; 
const int maxN = 2e3+10;
lli dp[maxN][maxN];


void dfs(int u, int root){
	for(auto v: adjList[u]) {
		if(next_node[v][root] != -1) continue;
		next_node[v][root] = u;
		dfs(v, root);
	}
}

lli f(int u, int v){
	if(u == v) return 1;

	lli &ans = dp[u][v];
	if(ans != -1) return ans;
    

	if(s[u-1] == s[v-1]) {
		if(next_node[u][v] == v) {
            return ans = 2;
        }

		ans = f(next_node[u][v], next_node[v][u]) + 2;
	}

	return ans = max({ans, f(next_node[u][v], v), f(u, next_node[v][u])});
}




void main_(){
	int n; cin>>n;
	cin>>s;

	adjList.clear();
	adjList.resize(n+1);
	next_node.assign(n+1, vector<int>(n+1, -1));

	for(int i = 0; i < n-1; i++) {
		int u, v; cin>>u>>v;
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}

	for(int i = 1; i <= n; i++) {
        next_node[i][i] = i;
		dfs(i, i);
	}


	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			dp[i][j] = -1;
		}
	}

    // for(int i = 1; i <= n; i++){
    //     cout << "u = " << i << endl;
    //     for(int j = 1; j <= n; j++) {
    //         cout << j << " -> " << next_node[i][j] << ",  ";
    //     }
    //     cout << endl;
    // }



	lli ans = 0;
	for(int l = 1; l <= n; l++) {
		for(int r = 1; r <= n; r++) {
			ans = max(ans, f(l, r));
		}
	}
	
	cout << ans << endl;


}


int main () {
	fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}