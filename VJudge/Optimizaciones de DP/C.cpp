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


const int MAXN = 2e5 + 100;

vector<pair<int,int>> adjList[MAXN];

bool visited[MAXN];
int value[MAXN];
const int INF = 1e9 + 10;

bool ok = true;
void dfs(int u, bool is_row, int me_val, int &min_delta, int &max_delta){
    

    if(visited[u]) {
        if(value[u] != me_val) {
            ok = false;
        }
        return;
    } else {
        value[u] = me_val;
    }

    visited[u] = true;
    
    // debugg(u);
    // debugg(visited[u]);

    if(is_row) {
        min_delta = max(min_delta, -me_val);
    } else {
        max_delta = min(max_delta, me_val);
    }
    
    for(auto [v, a]: adjList[u]){
        dfs(v, !is_row, a - me_val, min_delta, max_delta);
    }
}


int main () {
	//fastIO();

    int R, C; cin>>R>>C;
    int N; cin>>N;

    vector< tuple<int,int,int> > cells(N);
    for(auto &[r, c, a]: cells) cin>>r>>c>>a;

    for(auto &[r, c, a]: cells){
        r--, c--;
        adjList[r].push_back({R + c, a});
        adjList[R + c].push_back({r, a});
    }

    for(int i = 0; i < R+C; i++){
        if(visited[i]) continue;

        int val = 0;
        int min_delta = -INF, max_delta = INF;
        dfs(i, (i < R), val, min_delta, max_delta);
        if(min_delta > max_delta) ok = false;
    }

    cout << (ok ? "Yes" : "No") << endl;


	return 0;
}

