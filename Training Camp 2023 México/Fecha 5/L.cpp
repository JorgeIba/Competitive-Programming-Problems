#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

vector< vector<int> > adjList;
vector<int> height;


void dfs(int u){
    height[u] = 1;
    for(auto v: adjList[u]){
        dfs(v);
        height[u] = max(height[u], height[v] + 1); 
    }
}


void main_(){

    int n; cin>>n;

    adjList.clear();
    adjList.resize(n+1);

    height.clear();
    height.resize(n+1);
    
    for(int i = 2; i <= n; i++) {
        int p; cin>>p;
        adjList[p].push_back(i);
    }

    dfs(1);

    vector<int> fr(n+1);
    for(auto x: height) fr[x]++;

    int ans = n;
    for(int i = 1; i <= n; i++) {
        ans = min(ans, fr[i] + (i-1));
    }
    cout << ans << endl;
}


int main () {
	//fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

