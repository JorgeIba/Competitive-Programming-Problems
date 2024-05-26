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


void main_(){
	int n, k; cin>>n>>k;

    vector<int> nums(n);
    for(auto &x: nums){
        cin>>x;
        x--;
    }

    if(k == 1){
        bool ok = true;
        forn(i, n){
            if(nums[i] != i) ok = false;
        }
        cout << (ok ? "YES" : "NO") << endl;
        return;
    }


    vector<bool> visited(n);
    vector<int> colors(n);
    vector<int> start_cycle;
    auto dfs = [&](auto const &dfs, int u, int color) -> void {
        if(visited[u]){ 
            if(colors[u] == color){
                start_cycle.push_back(u);
            }
            return;
        }

        visited[u] = true;
        colors[u] = color;

        dfs(dfs, nums[u], color);
    };

    auto dfs_cycle = [&](const auto &dfs_cycle, int u, int &sz) {
        if(visited[u]) {
            return;
        }
        visited[u] = true;
        sz++;
        dfs_cycle(dfs_cycle, nums[u], sz);
    };


    int color = 1;
    forn(i, n){
        if(visited[i]) continue;

        dfs(dfs, i, color++);
    }

    vector<int> sz_cycles;
    fill(all(visited), false);
    for(auto x: start_cycle) {
        int sz = 0;
        dfs_cycle(dfs_cycle, x, sz);
        sz_cycles.push_back(sz);
    }
    

    bool ok = true;
    for(auto sz: sz_cycles){
        if(sz != k){
            ok = false;
        }
    }

    cout << (ok ? "YES" : "NO") << endl;

}


int main () {
	//fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

