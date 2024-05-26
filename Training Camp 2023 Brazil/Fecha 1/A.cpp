#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

vector< string > mat;
vector< vector<bool> > visited;

vector< pair<int,int> > all_dirs = {
    {0, 1},
    {1, 0},
    {-1, 0},
    {0, -1}
};

vector< pair<int,int> > dirs = {
    {0, 1},
    {1, 0},
};

bool is_inside(int x, int y) {
    int n = SZ(mat);
    return (0 <= x && x < n && 0 <= y && y < n);
}

bool dfs_reach(int x, int y){
    int n = SZ(mat);
    if(x == n-1 && y == n-1) return true;


    visited[x][y] = true;

    bool ans = false;
    for(auto [dx, dy]: all_dirs) {
        if(is_inside(x+dx, y+dy) && (mat[x+dx][y+dy] == '.') && !visited[x+dx][y+dy]){
            ans = ans || (dfs_reach(x+dx, y+dy));
        }
    }
    return ans;
}


#define uint unsigned int

const int maxN = 1010;
const int MOD = (1LL << 31) - 1;
lli dp[maxN][maxN];
lli dfs_ways(int x, int y) {
    int n = SZ(mat);
    if(x == n-1 && y == n-1) return 1;

    if(visited[x][y]) return dp[x][y];
    lli ans = 0;

    visited[x][y] = true;
    
    for(auto [dx, dy]: dirs){
        if(is_inside(x+dx, y+dy) && (mat[x+dx][y+dy] == '.')) {
            ans = (ans + dfs_ways(x+dx, y+dy)) % MOD;
        }
    }
    return dp[x][y] = ans;
}




int main () {
	//fastIO();

    int n; cin>>n;
    mat.resize(n);

    for(auto &x: mat) cin>>x;


    visited.assign(n, vector<bool>(n, false));
    bool test_reachable = dfs_reach(0, 0);


    visited.assign(n, vector<bool>(n, false));
    lli ans = dfs_ways(0, 0);

    if(ans != 0){
        cout << ans << endl;
    } else {
        if(test_reachable) {
            cout << "THE GAME IS A LIE" << endl;
        } else {
            cout << "INCONCEIVABLE" << endl;
        }
    }

	return 0;
}

