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
    Edge(int to, T capacity, bool rev = false): to(to), flow(0), capacity(capacity), rev(rev) {}
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
    T maxFlow = 0;

    Dinic(int N): N(N){
        adjList.resize(N);
        pos.resize(N);
        dist.resize(N);
    }

    void addEdge(int u, int v, T capacity, bool directed = true){
        Edge<T>* uv = new Edge<T>(v, capacity, false);
        Edge<T>* vu = new Edge<T>(u, directed?0:capacity, true);
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
	//fastIO();
    int n, m; cin>>n>>m;

    vector<string> mat(n);
    for(auto &s: mat) cin>>s;

    int s = 2*m, t = 2*m+1;

    Dinic<int> *D = new Dinic<int>(2*(m+1));

    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++) {
            if(i == j) continue;
            bool valid = true;
            bool is_same = true;

            
            for(int d = 0; d < n; d++) {
                valid = (valid && (mat[d][i] >= mat[d][j]));
                is_same = (is_same && mat[d][i] == mat[d][j]);
            }

            if(valid) {
                if(is_same) {
                    if(i < j) {
                        D->addEdge(i, m + j, 1, true);
                    }
                } else {
                    D->addEdge(i, m + j, 1, true);
                }
            }
        }

        D->addEdge(s, i, 1, true);
        D->addEdge(m+i, t, 1, true);
    }

    D->StartDinic(s, t);

    vector< vector<int> > adjList(m);
    vector<int> income_degree(m);

    for(int i = 0; i < m; i++) {
        for(auto E: D->adjList[i]) {
            if(E->rev || !E->flow) continue;
            auto v = E->to;

            adjList[i].push_back(v - m);
            income_degree[v-m]++;
        }
    }


    auto dfs = [&](const auto &dfs, int u, vector<int> &path) -> void {
        path.push_back(u);

        for(auto v: adjList[u]) {
            assert(SZ(adjList[u]) == 1);

            dfs(dfs, v, path);
        }
    };

    
    vector< vector<int> > paths;
    for(int i = 0; i < m; i++){
        if(income_degree[i]) continue;

        vector<int> path;
        dfs(dfs, i, path);

        paths.push_back(path);
    }

    int k = SZ(paths);
    cout << k << endl;

    vector< pair<int,int> > v_group(m);

    for(int i = 0; i < k; i++) {
        for(int j = 0; j < SZ(paths[i]); j++) {
            auto v = paths[i][j];
            v_group[v] = {i, j + 5};
        }
    }

    for(int i = 0; i < m; i++) {
        cout << v_group[i].first + 1 << " ";
    }   
    cout << endl;

    for(int i = 0; i < m; i++){
        cout << v_group[i].second << " ";
    }
    cout << endl;


    for(int d = 0; d < n; d++){
        vector< int > max_value_group(k, 1);
        for(int i = 0; i < m; i++) {
            if(mat[d][i] == '0') continue;

            auto [group, val] = v_group[i];

            max_value_group[group] = max(max_value_group[group], val);
        }

        for(int i = 0; i < k; i++){
            cout << max_value_group[i] << " ";
        }
        cout << endl;
    }

	return 0;
}

