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

struct Edge{
    lli to, flow, capacity;
    int idx;
    bool rev;
    Edge* res;
    Edge(int to, lli capacity, int idx, bool rev): to(to), flow(0), capacity(capacity), idx(idx), rev(rev) {}
    void addFlow(lli flow){
        this->flow += flow;
        this->res->flow -= flow;
    }
};
struct Dinic{
    vector< vector< Edge* > > adjList;
    vector< int > pos, dist;
    int N;
    lli limit = 1;
    lli maxFlow = 0;
    bool scaling;
    const lli INF = numeric_limits<lli>::max();

    Dinic(int N, bool withScaling = false): N(N), scaling(withScaling) {
        adjList.resize(N);
        pos.resize(N);
        dist.resize(N);
    }

    void addEdge(int u, int v, lli capacity, int idx, bool directed = true){
        Edge* uv = new Edge(v, capacity, idx, false);
        Edge* vu = new Edge(u, directed?0:capacity, idx, true);
        uv->res = vu;
        vu->res = uv;
        adjList[u].push_back(uv);
        adjList[v].push_back(vu);
    }

    lli BlockingFlow(int u, int t, lli flow){
        if(u == t) return flow;
        for(int &i= pos[u]; i<(int)adjList[u].size(); i++ ){
            Edge* E = adjList[u][i];
            if(E->capacity > E->flow && dist[E->to] == dist[u] + 1){
                lli f = BlockingFlow(E->to, t, min(flow, E->capacity - E->flow));
                if(f>0){
                    E->addFlow(f);
                    return f;
                }
            }
        }
        return 0;
    }
    bool bfs(int s, int t){
        fill(all(dist), -1);
        queue<lli> q; q.push(s);
        dist[s] = 0;
        while(!q.empty())
        {
            lli u = q.front(); q.pop();
            for(Edge* E: adjList[u])
            {
                if(dist[E->to] == -1 && E->capacity > E->flow && (!scaling || E->capacity - E->flow >= limit))
                {
                    dist[E->to] = dist[u] + 1;
                    q.push(E->to);
                }
            }
        }
        return dist[t] != -1;
    }
    
    lli StartDinic(int s, int t){
        maxFlow = 0;
        for(limit = (scaling?1<<30:1); limit>0; limit>>=1){ // (1<<30) is for maximum capacity = 10^9
            dist[t] = 0;
            while(bfs(s, t)){
                lli f = 0;
                fill(all(pos), 0);
                while((f = BlockingFlow(s, t, INF)))
                {
                    maxFlow += f;
                }
            }
        }
        return maxFlow;
    }
};



struct LowerBoundDinic: Dinic{
    vector< int > dem;
    int n;
    int s_prime = n, t_prime = n+1;

    LowerBoundDinic(int n): Dinic(n+2), dem(n), n(n), s_prime(n), t_prime(n+1) {}

    void addEdge(int u, int v, int l, int r, int idx) {
        dem[u] += l;
        dem[v] -= l;
        Dinic::addEdge(u, v, r - l, idx, true);
    }

    bool has_circulation() {
        lli total_dem = 0;
        for(int i = 0; i < n; i++){
            if(dem[i] < 0) {
                total_dem += -dem[i];
                addEdge(s_prime, i, 0, -dem[i], i);
            } else if(dem[i] > 0){
                addEdge(i, t_prime, 0, dem[i], i);
            }
        }

        return Dinic::StartDinic(s_prime, t_prime) == total_dem;
    }

    // lli maxFlow(int s, int t) {
    //     addEdge(s, t, 0, INF, N+1);
    //     if(!has_circulation()) return -1;

    //     Dinic::maxFlow = 0;
    //     return Dinic::StartDinic(s, t);
    // }
};



int main () {
	fastIO();

    #ifdef ONLINE_JUDGE
    freopen("cooling.in", "r", stdin);
    freopen("cooling.out", "w", stdout);
    #endif
	

    int n, m; cin>>n>>m;
    LowerBoundDinic *LBD = new LowerBoundDinic(n);

    vector<int> lowers(m);
    forn(i, m){
        int u, v, l, r; cin>>u>>v>>l>>r; 
        u--, v--;
        LBD->addEdge(u, v, l, r, i);
        lowers[i] = l;
    }



    if(!LBD->has_circulation()) {
        cout << "NO" << endl;
        return 0;
    }

    vector<int> ans(m);
    for(int i = 0; i < n; i++) {
        for(auto v: LBD->adjList[i]) {
            if(v->rev) continue;
            if(v->to == LBD->t_prime) continue;
            ans[v->idx] = v->flow + lowers[v->idx];
        }
    }

    cout << "YES" << endl;
    for(auto x: ans) cout << x << endl;
	


	return 0;
}

