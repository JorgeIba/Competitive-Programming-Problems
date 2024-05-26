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

const int MAXN = 5000 + 100;
vector<int> adjList[MAXN];


ld dp[MAXN][MAXN];
bool visited[MAXN][MAXN];


ld f(int left, int right){
    if(left < 0 || right < 0) return 0;

    if(left == 0) return 1.0 / (right+1);

    bool &vis = visited[left][right];
    ld &ans = dp[left][right];

    if(vis) return ans;
    vis = true;
    ans = 0;


    ld yes = ld(left-1) / (left+right+1) * f(left-2, right);
    ld no = ld(right) / (left+right+1) * f(left-1, right-1);

    return ans = (yes + no);
}   


void main_(){
    int n, m; cin>>n>>m;

    forn(i, m){
        int u, v; cin>>u>>v; u--, v--;
        adjList[u].push_back(v);
    }

    vector<ld> dp_1(n);
    dp_1[n-1] = 1;
    
    for(int u = n-2; u >= 0; u--){

        sort(all(adjList[u]), [&](auto x, auto y){
            return dp_1[x] > dp_1[y];
        });

        int k = SZ(adjList[u]);
        for(int i = 0; i < k; i++) {
            int v = adjList[u][i];
            // cout << v << " -> " << i << " -- " << k-i-1 << " .. " << dp_1[v] << " prob: " << f(i, k - i - 1) << endl;
            dp_1[u] += dp_1[v] * f(i, k - i - 1);
        }
    }

    cout << fixed << setprecision(20) << dp_1[0] << endl;


    forn(i, n) adjList[i].clear();
}


int main () {
	fastIO();


	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

