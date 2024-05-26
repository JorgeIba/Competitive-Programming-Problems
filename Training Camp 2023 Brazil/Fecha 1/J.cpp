#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

int main () {
	fastIO();

    int n, m; cin>>n>>m;

    vector< vector<int> > adjList(n+1);
    for(int i = 0; i < m; i++){
        int u, v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    vector< set<int> > groups(4);

    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 4; j++) {

            bool poss = true;
            for(auto v: adjList[i]) {
                if(groups[j].count(v)) {
                    poss = false;
                }   
            }

            if(poss) {
                groups[j].insert(i);
                break;
            }
        }
    }




    int ans = 0;
    for(int i = 0; i < 4; i++) {
        ans += (SZ(groups[i]) > 0);
    }

    cout << ans << endl;
    for(int i = 0; i < 4; i++) {
        if(SZ(groups[i])) {
            for(auto x: groups[i]) {
                cout << x << " ";
            }
            cout << endl;
        }
    }




	return 0;
}

