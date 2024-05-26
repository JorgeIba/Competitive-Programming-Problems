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


const int MAXN = 2e5 + 100;

vector<tuple<int,lli,lli>> adjList[MAXN];

void main_(){
    int n, m; cin>>n>>m;

    forn(i, m){
        int u, v, x, y; cin>>u>>v>>x>>y;
        u--, v--;
        adjList[u].push_back({v, x, y});
        adjList[v].push_back({u, -x, -y});
    }

    map< int, pair<lli,lli> > pos;
    queue<int> q;

    q.push(0);
    pos[0] = {0, 0};

    while(!q.empty()){
        auto u = q.front(); q.pop();

        for(auto [v, x, y]: adjList[u]){
            if(pos.count(v)) continue;

            pos[v] = {pos[u].first + x, pos[u].second + y};
            q.push(v);
        }
    }

    forn(i, n){
        if(pos.count(i)){
            cout << pos[i].first << " " << pos[i].second << endl;
        } else {
            cout << "undecidable" << endl;
        }
    }


}


int main () {
	//fastIO();
	
	int t = 1;
	// cin>>t;
	
	while(t--) main_();


	return 0;
}

