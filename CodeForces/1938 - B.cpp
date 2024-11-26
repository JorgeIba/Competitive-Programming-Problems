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


const int MAXN = 1e5 + 100;
const int MAXA = 5;
map<int,lli> adjList[MAXN];
const lli INF = 1e18;
lli B = 1e6;

int main () {
	// fastIO();

    int n, m; cin>>n>>m;

    forn(i, n) {
        int x, y; cin>>x>>y;
    }

    lli ans = 0;
    forn(i, m) {
        int u, v, w; cin>>u>>v>>w;
        u--, v--;
        adjList[u][v] = w;
        adjList[v][u] = w;
        ans = max(ans, 1LL*w);
    }

    set< pair<int,int> > order;
    forn(i, n) {
        order.insert({SZ(adjList[i]), i});
    }

    vector< vector<int> > mask_per_cnt(MAXA+1);
    for(int mask = 0; mask < (1 << MAXA); mask++) {
        int cnt = __builtin_popcount(mask);
        mask_per_cnt[cnt].push_back(mask);
    }

    vector<lli> incident_sum(n);

    auto get_cnt_sum = [&](const vector<int> &nodes) -> pair<int,lli> {
        int cnt = 0;
        lli sum = 0;

        for(auto v: nodes)
            incident_sum[v] = 0;

        int m = SZ(nodes);
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < i; j++) {
                auto itr = adjList[nodes[i]].find(nodes[j]);
                if(itr != adjList[nodes[i]].end()) {
                    cnt++;
                    sum += itr->second;
                    incident_sum[nodes[i]] += itr->second;
                    incident_sum[nodes[j]] += itr->second;
                }          
            }
        }

        return {cnt, sum};
    };

    auto nC2 = [&](lli n) {
        return n * (n-1) / 2;
    };
    auto complete = [&](lli n) {
        return 3 * (n-2);
    };

    map< vector<int>, lli > best;

    // // get ans when u has smallest degree
    auto f = [&](int u) {
        int k = SZ(adjList[u]);
        for(int cnt_other = k; cnt_other >= 2; cnt_other--) {
            for(auto mask: mask_per_cnt[cnt_other]) {
                if(mask > (1 << (k))) break;

                vector<int> nodes = {u};
                int j = 0;
                for(auto itr = adjList[u].begin(); itr != adjList[u].end(); itr++, j++) {
                    if(mask & (1 << j)) {
                        nodes.push_back(itr->first);
                    }
                }

                sort(all(nodes));

                auto [total_edges, total_sum] = get_cnt_sum(nodes);

                lli total_sz = cnt_other + 1;
                if(total_edges != complete(total_sz)) continue;


                lli cost = total_sum - B * (nC2(total_sz) - total_edges) * (nC2(total_sz) - total_edges);
                ans = max(ans, cost);

                // One is left
                {
                    for(int i = 0; i < total_sz; i++) {
                        auto nodes_1 = nodes;
                        nodes_1.erase(nodes_1.begin() + i);

                        if(!best.count(nodes_1)) continue;

                        lli cost_one_left = (total_sum + best[nodes_1]) - B;
                        ans = max(ans, cost_one_left);
                    }
                }

                {
                    for(int i = 0; i < total_sz; i++) {
                        auto nodes_1 = nodes;
                        nodes_1.erase(nodes_1.begin() + i);

                        if(!best.count(nodes_1))
                            best[nodes_1] = -INF;
                        
                        best[nodes_1] = max(best[nodes_1], incident_sum[nodes[i]]);
                    }
                }
            }
        }
    };


    vector<bool> visited(n);
    while(!order.empty()) {
        auto itr_small = order.begin();
        auto [sz, u] = *itr_small; order.erase(itr_small);

        if(visited[u]) continue;
        visited[u] = true;

        assert(sz <= MAXA);
        f(u);

        for(auto [v, w]: adjList[u]) {
            adjList[v].erase(u);
            order.insert({SZ(adjList[v]), v});
        }
        adjList[u].clear();
    }


    cout << ans << endl;

	return 0;
}

