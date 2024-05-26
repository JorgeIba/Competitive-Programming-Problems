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
    bool rev;
    Edge* res;
    int idx;
    Edge(int to, T capacity, bool rev = false, int idx = -1): to(to), flow(0), capacity(capacity), rev(rev), idx(idx) {}
    void addFlow(T flow){
        this->flow += flow;
        this->res->flow -= flow;
    }
};

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

    void addEdge(int u, int v, T capacity, bool directed = true, int idx = -1){
        Edge<T>* uv = new Edge<T>(v, capacity, false, idx);
        Edge<T>* vu = new Edge<T>(u, directed?0:capacity, true, idx);
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
                if(dist[E->to] == -1 && E->capacity > E->flow && (!scaling || E->capacity - E->flow >= limit)){
                    dist[E->to] = dist[u] + 1;
                    q.push(E->to);
                }
            }
        }
        return dist[t] != -1;
    }
    
    T StartDinic(int s, int t){
        maxFlow = 0;
        
        dist[t] = 0;
        while(bfs(s, t)){
            lli f = 0;
            fill(all(pos), 0);
            while((f = BlockingFlow(s, t, INF))){
                maxFlow += f;
            }
        }
        return maxFlow;
    }
};

int main () {
	// fastIO();
	
    // freopen("heavy.in","r",stdin);
    // freopen("heavy.out","w",stdout);

    int n, k; cin>>n>>k;

    vector<string> ss(n);
    for(auto &s: ss) cin>>s;

    map< string, int > prefs_map, suffs_map;
    vector< pair<int,int> > indexes;

    for(auto s: ss){
        int m = SZ(s);
        auto pref = s.substr(0, k);
        auto suff = s.substr(m - k, k);

        if(!prefs_map.count(pref))
            prefs_map[pref] = SZ(prefs_map);

        if(!suffs_map.count(suff))
            suffs_map[suff] = SZ(suffs_map);

        indexes.push_back({prefs_map[pref], suffs_map[suff]});
    }


    vector<string> prefs(SZ(prefs_map)), suffs(SZ(suffs_map));
    for(auto [pref, id]: prefs_map) prefs[id] = pref;
    for(auto [suff, id]: suffs_map) suffs[id] = suff;

    int left  = SZ(prefs);
    int right = SZ(suffs);

    int s = left + right, t = s+1;
    Dinic D(t+1);

    forn(i, left){
        D.addEdge(s, i, 1);
    }

    forn(i, right){
        D.addEdge(left + i, t, 1);
    }

    forn(i, n){
        auto [id_pref, id_suff] = indexes[i];
        D.addEdge(id_pref, left + id_suff, 1, 1, i);
    }


    auto ans = D.StartDinic(s, t);

    vector<bool> visited(t+1);
    auto dfs = [&](const auto &dfs, int u){
        if(visited[u]) return;
        visited[u] = true;

        for(auto E: D.adjList[u]) {
            if(E->flow == E->capacity) continue;
            dfs(dfs, E->to);
        }
    };

    for(auto E: D.adjList[s]){
        if(E->flow == E->capacity) continue;
        dfs(dfs, E->to);
    }

    vector<int> min_cover_vertex;
    forn(i, left){
        if(!visited[i]){
            min_cover_vertex.push_back(i);
        }
    }

    forn(i, right){
        if(visited[left + i]){
            min_cover_vertex.push_back(left+i);
        }
    }

    vector<int> already(n);
    cout << ans << endl;
    for(auto x: min_cover_vertex){
        vector<int> edges;
        if(x < left){
            for(auto E: D.adjList[x]){
                if(E->rev) continue;
                if(!already[E->idx])
                    edges.push_back(E->idx);
            }
        } else {
            for(auto E: D.adjList[x]){
                if(!E->rev) continue;
                if(!already[E->idx])
                    edges.push_back(E->idx);
            }
        }

        sort(all(edges));
        cout << SZ(edges) << " ";
        for(auto idx: edges){
            already[idx] = true;
            cout << idx + 1 << " ";
        }
        cout << endl;
    }

    





	return 0;
}

