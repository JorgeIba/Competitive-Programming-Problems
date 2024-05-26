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


int main () {
	fastIO();
	
    int n; cin>>n;
    vector<int> perm(n+1);
    forr(i, 1, n) cin>>perm[i];

    vector<int> income(n+1);
    forr(i, 1, n){
        income[perm[i]]++;
    }

    queue<int> q;
    vector<int> circled(n+1, -1);
    forr(i, 1, n){
        if(income[i] == 0){
            q.push(i);
            circled[i] = 0;
        }
    }

    vector<bool> deleted(n+1);

    while(!q.empty()) {
        auto u = q.front(); q.pop();
        auto v = perm[u];

        if(circled[v] == 0) {
            cout << -1 << endl;
            return 0;
        }

        circled[v] = 1;

        if(!deleted[v]) {
            income[perm[v]]--;
            if(income[perm[v]] == 0) {
                q.push(perm[v]);
                circled[perm[v]] = 0;
            }
            deleted[v] = true;
        }
    }

    vector<bool> visited(n+1);
    auto dfs = [&](const auto &dfs, int u, int &sz) -> void {
        if(visited[u]) return;
        sz++;
        visited[u] = true;
        circled[u] = (sz+1)%2;
        dfs(dfs, perm[u], sz);
    };

    forr(i, 1, n){
        if(circled[i] == -1) {
            assert(visited[i] == false);
            int sz = 0;
            dfs(dfs, i, sz);
            if(sz & 1) {
                cout << -1 << endl;
                return 0;
            }
        }
    }


    vector<int> ans;
    forr(i, 1, n) if(circled[i] == 0){
        ans.push_back(perm[i]);
    }
    
    cout << SZ(ans) << endl;
    for(auto x: ans) cout << x << " ";
    cout << endl;



	return 0;
}


