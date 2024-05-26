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

const int MAXN = 1e5+100;
ld dp[MAXN];
int sizes[MAXN];

vector<int> adjList[MAXN];

void dfs(int u){
    sizes[u] = 1;
    for(auto v: adjList[u]){
        dfs(v);
        sizes[u] += sizes[v];
    }
}

void dfs_ans(int u){
    for(auto v: adjList[u]){
        int size_siblings = (sizes[u]-1 - sizes[v]);
        dp[v] = (dp[u]+1) + (ld)(size_siblings)/2;
        dfs_ans(v);
    }
}



int main () {
	//fastIO();
	
	int n; cin>>n;
    forn(i, n-1){
        int p; cin>>p; p--;
        adjList[p].push_back(i+1);
    }

    dp[0] = 1; 
    dfs(0);
    dfs_ans(0);

    cout << fixed << setprecision(10);
    forn(i, n) {
        cout << dp[i] << " ";
    }
    cout << endl;


	return 0;
}

