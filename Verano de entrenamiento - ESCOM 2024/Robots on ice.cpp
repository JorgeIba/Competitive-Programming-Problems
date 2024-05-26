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

const int DIRS = 4;
int DX[DIRS] = {-1, 0, 0, +1};
int DY[DIRS] = {0, -1, 1, 0};


const int MAX_C = 3;
int Rs[MAX_C];
int Cs[MAX_C];
int Ts[MAX_C];


const int MAX_N = 8;
bool visited[MAX_N][MAX_N];
int comps[MAX_N][MAX_N];


int n, m;


bool is_inside(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < m;
};

bool is_valid(int x, int y, int timee) {
    forn(i, MAX_C){
        int r = Rs[i], c = Cs[i], t = Ts[i];
        if(r == x && c == y) {
            if(t != timee) return false;
        }
    }
    return true;
};

bool prunning_distance(int x, int y, int timee) {
    int total_dist = timee;
    int curr_x = x, curr_y = y;
    forn(i, MAX_C){
        int r = Rs[i], c = Cs[i], t = Ts[i];
        if(visited[r][c]) continue;
        int dis = abs(curr_x - r) + abs(curr_y - c);
        total_dist += dis;
        if(total_dist > t) return false;
        curr_x = r, curr_y = c;
    }
    return true;
};


void dfs_comps(int x, int y, int comp){
    comps[x][y] = comp;
    forn(i, DIRS){
        int dx = DX[i], dy = DY[i];
        if(!is_inside(x + dx, y + dy)) continue;
        if(comps[x+dx][y+dy]) continue;
        if(visited[x+dx][y+dy]) continue;
        dfs_comps(x+dx, y+dy, comp);
    }
};

bool prunning_division() {
    forn(i, n)
        forn(j, m)
            comps[i][j] = 0;
    
    int comp = 1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(comps[i][j] == 0 && visited[i][j] == false) {
                if(comp == 2) return false;
                dfs_comps(i, j, comp++);
            }
        }
    }
    return true;
};

bool is_wall(int x, int y) {
    return (x == 0) || (x == n-1) || (y == 0) || (y == m-1);
};
bool check_wall(int x, int y){
    if(!is_wall(x,y)) return true;
    if(x == 0 || x == n-1) {
        auto left = is_inside(x, y-1) && !visited[x][y-1];
        auto right = is_inside(x, y+1) && !visited[x][y+1];
        return !(left && right);
    }

    if(y == 0 || y == m-1) {
        auto up = is_inside(x-1, y) && !visited[x-1][y];
        auto down = is_inside(x+1, y) && !visited[x+1][y];
        return !(up && down);  
    } 
    return true;
};


int cnt_calls;
lli dfs(int x, int y, int timee){
    if(x == 0 && y == 1) return (lli) (timee == n*m);
    cnt_calls++;

    if(!is_valid(x, y, timee)) return 0LL;
    if(!prunning_distance(x, y, timee)) return 0LL;
    if(!check_wall(x, y)) return 0LL;
    if(!prunning_division()) return 0LL;


    lli ans = 0;
    // for(auto [dx, dy]: dirs) {
    forn(i, DIRS){
        int dx = DX[i], dy = DY[i];
        if(!is_inside(x+dx, y+dy)) continue;
        if(visited[x+dx][y+dy]) continue;

        visited[x+dx][y+dy] = 1;
        ans += dfs(x+dx, y+dy, timee+1);
        visited[x+dx][y+dy] = 0;
    }

    return ans;
};


void main_(int test){
    forn(i, MAX_C){
        cin>>Rs[i]>>Cs[i];
        Ts[i] = (i+1) * n * m / 4;
    }
    forn(i,n)
        forn(j,m)
            visited[i][j] = false;



    cnt_calls = 0;


    visited[0][0] = 1;
    lli ans = dfs(0, 0, 1);
    // debugg(cnt_calls);
    cout << "Case " << test << ": " << ans << endl;
}


int main () {
	// fastIO();

    int t = 1;
    while(true) {
        // int n, m; cin>>n>>m;
        cin>>n>>m;
        if(n == 0 && m == 0) break;
        main_(t++);
    }

	return 0;
}

