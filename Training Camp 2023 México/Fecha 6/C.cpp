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

template<typename T = int>
struct Edge{
    int to;
    T flow, capacity;
    int idx;
    bool rev;
    Edge* res;
    Edge(int to, T capacity, int idx, bool rev = false): to(to), flow(0), capacity(capacity), idx(idx), rev(rev) {}
    void addFlow(T flow){
        this->flow += flow;
        this->res->flow -= flow;
    }
};

//MUCHO OJO CON ESTO
const int INF = 1e9;

template<typename T = int>
struct Dinic{
    vector< vector< Edge<T>* > > adjList;
    vector< int > pos, dist;
    int N;
    T limit = 1;
    T maxFlow = 0;
    const bool scaling = false;


    Dinic(int N): N(N){
        adjList.resize(N);
        pos.resize(N);
        dist.resize(N);
    }

    void addEdge(int u, int v, T capacity, int idx, bool directed = true){
        Edge<T>* uv = new Edge<T>(v, capacity, idx, false);
        Edge<T>* vu = new Edge<T>(u, directed?0:capacity, idx, true);
        uv->res = vu;
        vu->res = uv;
        adjList[u].push_back(uv);
        adjList[v].push_back(vu);
    }

    T BlockingFlow(int u, int t, T flow){
        if(u == t) return flow;
        for(int &i= pos[u]; i<(int)adjList[u].size(); i++ ){
            Edge<T>* E = adjList[u][i];
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
        queue<int> q; q.push(s);
        dist[s] = 0;
        while(!q.empty()){
            lli u = q.front(); q.pop();
            for(auto E: adjList[u]){
                if(dist[E->to] == -1 && E->capacity > E->flow){
                    dist[E->to] = dist[u] + 1;
                    q.push(E->to);
                }
            }
        }
        return dist[t] != -1;
    }

    void resetFlow() {
        for(int i = 0; i < SZ(adjList); i++){
            for(auto &v: adjList[i]){
                v->flow = 0;
            }
        }
    }
    
    T StartDinic(int s, int t){
        maxFlow = 0;
        
        dist[t] = 0;
        while(bfs(s, t)){
            lli f = 0;
            fill(all(pos), 0);
            while((f = BlockingFlow(s, t, INF)))
            {
                maxFlow += f;
            }
        }
    
        return maxFlow;
    }
};

template<typename T = int>
struct LowerBoundDinic: Dinic<T>{
    vector< T > dem;
    int n;
    int s_prime = n, t_prime = n+1;
    vector< int > lowers; 
    int timee = 0;
    T total_dem = 0;

    LowerBoundDinic(int n): Dinic<T>(n+2), dem(n), n(n), s_prime(n), t_prime(n+1) {}

    void addEdge(int u, int v, T l, T r) {
        dem[u] += l;
        dem[v] -= l;
        lowers.push_back(l);
        Dinic<T>::addEdge(u, v, r - l, timee++); // idx = timee++
    }

    bool has_circulation() {
        
        for(int i = 0; i < n; i++){
            if(dem[i] < 0) {
                total_dem += -dem[i];
                Dinic<T>::addEdge(s_prime, i, -dem[i], 0);
            } else if(dem[i] > 0){
                Dinic<T>::addEdge(i, t_prime, dem[i], 0);
            }
            dem[i] = 0;
        }

        return Dinic<T>::StartDinic(s_prime, t_prime) == total_dem;
    }

    // Calculate the minimum flow feasible with lower bounds
    T getMinFlow(int s, int t) {
        addEdge(t, s, 0, INF);
        if(!has_circulation()) return -1;

        auto change_flow_t = [&](T k) {
            for(auto &v: Dinic<T>::adjList[t]) {
                if(v->to == s) {
                    v->capacity = k;
                    v->res->capacity = k;
                }
            }
        };

        int l = 0, r = INF, ans = INF;
        while(l <= r) {
            int mid = l + (r-l)/2;

            Dinic<T>::resetFlow();

            change_flow_t(mid);

            if(has_circulation()) {
                r = mid-1;
                ans = mid;
            } else {
                l = mid+1;
            }
        }

        Dinic<T>::resetFlow();
        change_flow_t(ans);
        has_circulation();

        return ans;
    }

    // Calculate the maximum flow feasible
    T getMaxFlow(int s, int t) {
        addEdge(t, s, 0, INF);
        if(!has_circulation()) return -1;

        Dinic<T>::maxFlow = 0;
        return Dinic<T>::StartDinic(s, t);
    }
};


int main () {
	// fastIO();
    
    #ifdef ONLINE_JUDGE
    freopen("inspection.in", "r", stdin);
    freopen("inspection.out", "w", stdout);
    #endif

    int n; cin>>n;

    int s = n, t = s+1;
    
    LowerBoundDinic<int> *LBD = new LowerBoundDinic<int>(n+2);

    vector< int > income(n), outcome(n);

    for(int u = 0; u < n; u++) {
        int m; cin>>m;
        for(int j = 1; j <= m; j++){
            int v; cin>>v; 
            v--;
            LBD->addEdge(u, v, 1, INF);
            income[v]++;
            outcome[u]++;
        }
    }

    for(int u = 0; u < n; u++){
        if(!income[u])
            LBD->addEdge(s, u, 0, INF);
        if(!outcome[u])
            LBD->addEdge(u, t, 0, INF);
    }


    auto ans = LBD->getMinFlow(s, t);


    for(int u = 0; u < n; u++){
        for(auto &v: LBD->adjList[u]){
            if(v->rev) continue;

            auto to_add = LBD->lowers[ v->idx ];
            v->flow += to_add;
            v->capacity += to_add;
        }
    }

    vector< vector<int> > ans_paths;
    auto dfs = [&](auto dfs, int u, vector<int> path) {
        if(u == t) {
            ans_paths.push_back(path);
            return true;
        }

        path.push_back(u);

        for(auto &v: LBD->adjList[u]){
            if(v->flow && !v->rev && v->to != LBD->t_prime) {
                if(dfs(dfs, v->to, path)) {
                    v->flow--;
                    return true;
                }
                    
            }
        }
        return false;
    };

    while (true){
        bool valid = false;
        for(auto &v: LBD->adjList[ s ]) {
            if(v->flow && !v->rev && v->to != LBD->t_prime) {
                if(dfs(dfs, v->to, {})){
                    v->flow--;
                    valid = true;
                }
            }
        }
        if(!valid) break;
    }
    
    cout << ans << endl;
    for(auto &v: ans_paths){
        for(auto x: v) cout << x+1 << " ";
        cout << endl;
    }


	return 0;
}

