#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;



int n, m; 
int x_start, y_start; 
int x_end, y_end;
vector< vector<int> > mat;
vector< vector<bool> > visited;

vector< pair<int,int> > dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

bool inside(int x, int y){
    if(0 <= x && x < n && 0 <= y && y < m) return true;
    return false;
}


bool check(int mask, int x, int y) {
    if(! (mask & (1 << mat[x][y])))
        return false;

    if(x == x_end && y == y_end)
        return true;

    visited[x][y] = true;
    for(auto [dx, dy]: dir) {
        if(inside(x + dx, y + dy) && !visited[x+dx][y+dy])
            if(check(mask, x+dx, y+dy))
                return true;
    }
    return false;
}


int main () {
	//fastIO();
	
    cin>>n>>m;

    cin>>x_start>>y_start; 
    cin>>x_end>>y_end; 

    x_start--, y_start--;
    x_end--, y_end--;

    mat.assign(n, vector<int>(m));
    for(auto &v: mat) {
        for(auto &x: v){
            cin>>x;
            x--;
        }
    }
            

    int ans = 10;
    for(int mask = 0; mask < (1 << 10); mask++){
        visited.assign(n, vector<bool>(m, false));
        if(check(mask, x_start, y_start)){
            ans = min(ans, __builtin_popcount(mask));
        }
    }

    cout << ans << endl;



	return 0;
}

