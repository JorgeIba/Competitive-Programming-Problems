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

const int MAXN = 1e5 + 100;

vector< pair<int,int> > adjList[MAXN];

int main () {
	fastIO();
	
	int n, m; cin>>n>>m;

	vector< tuple<int,int,int,int> > edges;
	forn(i, m){
		int u, v, w; cin>>u>>v>>w; u--, v--;
		adjList[u].push_back({v, w});

		edges.push_back({u, v, w, i});
	}

    vector<int> depth(n);
	auto check = [&](lli max_k){
        vector<int> income(n);
        for(auto [u, v, w, idx]: edges){
            if(w <= max_k) continue;

            income[v]++;
        }

        fill(all(depth), 0);

        queue<int> q;
        forn(i, n) if(income[i] == 0){
            q.push(i);
        }

        int cnt = 0;
        while(!q.empty()){
            auto u = q.front(); q.pop();

            cnt++;

            for(auto [v, w]: adjList[u]){
                if(w <= max_k) continue;

                income[v]--;
                if(!income[v]) {
                    depth[v] = depth[u] + 1;
                    q.push(v);
                }
                    
            }
        }

        return cnt == n;
	};


	lli l = 0, r = 1e9+10, ans = r;

	while(l <= r){
		lli mid = (l+r) / 2;
		if(check(mid)){
			ans = mid;
			r = mid-1;
		} else {
			l = mid+1;
		}
	}

    check(ans);

    vector<int> ans_v;
    for(auto [u, v, w, idx]: edges){
        if(w > ans) continue;

        if(! (depth[u] < depth[v] || (depth[u] == depth[v] && u < v)) ) {
            ans_v.push_back(  idx  );
        }
    }

    cout << ans << " " << SZ(ans_v) << endl;
    for(auto x: ans_v){
        cout << x+1 << " ";
    }
    cout << endl;


	return 0;
}
