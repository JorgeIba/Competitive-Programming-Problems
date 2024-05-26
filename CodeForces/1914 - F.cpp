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

const int MAXN = 2e5 + 10;

vector<int> adjList[MAXN];


void dfs(int u, int level, vector<int> &levels) {
    levels[level]++;
    for(auto v: adjList[u]) {
        dfs(v, level+1, levels);
    }
}



void main_(){
    int n; cin>>n;

    forr(i, 1, n-1) {
        int p; cin>>p; p--;
        adjList[p].push_back(i);
    }

    vector<int> levels(n);
    dfs(0, 0, levels);


    int ans = 0;
    int wildcards = 0;
    for(int i = n-1; i > 0; i--) {
        if(levels[i] == 0) continue;

        if(levels[i] > 1) {
            int pairs = min(wildcards, levels[i]-1);
            wildcards -= pairs;
            levels[i] -= pairs;
            ans += pairs;

            // emparejar mismo nivel
            ans += levels[i] / 2;
            wildcards += levels[i] % 2;
        } else {
            assert(levels[i] == 1);
            wildcards++;
        }
    }
    
    cout << ans << endl;

    forn(i, n)
        adjList[i].clear();
}

int main () {
	fastIO();

	int t = 1; 
	cin>>t;

	while(t--) {
		main_();
	}

	return 0;
}
