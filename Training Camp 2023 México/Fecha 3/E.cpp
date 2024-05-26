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

const int MAXN = 1e5+100;
const int INF = 1e9;


struct Edge{
    int to;
    int flow, cap, cost;
    Edge* res = NULL;
    Edge(int to, int cap, int cost): to(to), flow(0), cap(cap), cost(cost) {}

    void addFlow(int flow) {
        this->flow += flow;
        this->res->flow -= flow;
    }
};


vector< Edge* > adjList[MAXN];
pair<int, Edge* > dp[MAXN]; // lowest_dist, direction

int cap[MAXN];
Edge* to_t[MAXN];
int n, m; 
int t;

Edge* addEdge(int u, int v, int cap, int cost) {
    Edge* uv = new Edge(v, cap, cost);
    Edge* vu = new Edge(u, 0,  -cost);

    uv->res = vu;
    vu->res = uv;

    adjList[u].push_back(uv);
    adjList[v].push_back(vu);
    return uv;
}


void update_node(int s){
    auto get_dp = [&](int u) -> pair<int,Edge*>{
        if(1 <= u && u <= n) return dp[u];
        return {INF, NULL};
    };

    auto left = get_dp(2*s);
    auto right = get_dp(2*s + 1);


    Edge* best_left = NULL;
    for(auto E: adjList[s]) {
        if(E->to != 2*s) continue;

        if(E->flow < E->cap) {
            if(!best_left || E->cost < best_left->cost) {
                best_left = E;
            }
        }
    }

    Edge* best_right = NULL;
    for(auto E: adjList[s]) {
        if(E->to != 2*s + 1) continue;

        if(E->flow < E->cap) {
            if(!best_right || E->cost < best_right->cost) {
                best_right = E;
            }
        }
    }


    left.first  += best_left  ? best_left->cost  : INF;
    right.first += best_right ? best_right->cost : INF;

    if(to_t[s] && to_t[s]->flow < to_t[s]->cap) {
        dp[s] = {0, to_t[s]};
    } else {
        dp[s] = {INF, NULL};
    }

    int ans_min = min({dp[s].first, left.first, right.first});

    if(ans_min == left.first) {
        dp[s] = left;
        dp[s].second = best_left;
    } else if(ans_min == right.first) {
        dp[s] = right;
        dp[s].second = best_right;
    }
}


void update_ancestors(int s, int lca){
    for(int u = s; u != lca; u >>= 1) {
        Edge* from = NULL;
        for(auto E: adjList[u]) {
            if(E->to != (u >> 1)) continue;

            if(E->flow < E->cap) {
                if(!from || E->cost < from->cost) {
                    from = E;
                }
            }
        }

        assert(from);
        from->addFlow(1);
    }
}


// {Min cost, lca, final_v}
tuple<int,int,int, vector<Edge*>> find_path(int s){
    pair<int,int> best_way = {INF, INF};


    int dist = 0;
    for(int u = s; u >= 1; u >>= 1) {
        pair<int,int> opt = {dist + dp[u].first, u};
        best_way = min(best_way, opt);

        int min_cost_parent = INF;
        for(auto E: adjList[u]) {
            if(E->to != (u >> 1)) continue;

            if(E->flow < E->cap) {
                min_cost_parent = min(min_cost_parent, E->cost);
            }
        }

        dist += min_cost_parent;
    }

    assert(best_way.first < INF);
    int v = best_way.second;
    int lca = v;

    vector<Edge*> path_to_v;
    while(true) {
        path_to_v.push_back(dp[v].second);
        if(dp[v].second->to == t) break;
        v = dp[v].second->to;
    }

    return {best_way.first, lca, v, path_to_v};
}


void prec_dp() {
    for(int i = n; i >= 1; i--){
        update_node(i);
    }
}

void prec_network() {
    auto is_valid = [&](int u){
        return (1 <= u && u <= n);
    };

    for(int i = 1; i <= n; i++){
        int p = i / 2;
        if(is_valid(p)) {
            addEdge(i, p, INF, 1);
            addEdge(p, i, INF, 1);
        }
    }

    for(int i = 1; i <= n; i++){
        if(cap[i]) {
            auto E = addEdge(i, t, cap[i], 0);
            to_t[i] = E;
        }
    }
}


int main () {
	fastIO();


    #ifdef ONLINE_JUDGE
        freopen("mole.in", "r", stdin);
        freopen("mole.out", "w", stdout);
    #endif



    forn(i, MAXN) {
        dp[i] = {INF, NULL};
        to_t[i] = NULL;
    }

    cin>>n>>m;
    t = n+1;

    forr (i, 1, n) {
        cin>>cap[i];
    }

    prec_network();

    vector<int> sources(m);
    for(auto &x: sources) cin>>x;

    prec_dp();

    int ans = 0;
    for(auto u: sources){

        auto [cost, lca, v, path] = find_path(u);

        ans += cost;

        for(auto &E: path) 
            E->addFlow(1);


        update_ancestors(u, lca);

        for(int anc = u; anc >= 1; anc >>= 1)
            dp[anc] = {INF, NULL};

        for(int anc = v; anc >= 1; anc >>= 1) 
            dp[anc] = {INF, NULL};

        for(int anc = u; anc >= 1; anc >>= 1)
            update_node(anc);

        for(int anc = v; anc >= 1; anc >>= 1)
            update_node(anc);


        cout << ans << " ";
    }
    cout << endl;

    
	return 0;
}

