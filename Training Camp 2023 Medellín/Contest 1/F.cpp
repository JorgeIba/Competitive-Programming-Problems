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

const lli INF = 1e15;
const lli INF_D = 1e9;

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


vector< pair<int,int> > dir = {
        {-1, 0},
    {0,-1}, {0, 1},
        {1, 0}
};


int main () {
	//fastIO();
	
    int n, m, c; cin>>n>>m>>c;
    swap(n, m);

    vector< string > mat(n);
    for(auto &s: mat) cin>>s;

    vector<int> cost(c);
    for(auto &x: cost) cin>>x;


    auto is_inside = [&](int i, int j){
        if(i < 0 || i >= n || j < 0 || j >= m) return false;
        return true;
    };

    auto mapping = [&](int i, int j, bool out) {
        return 2*(i * m + j) + out;
    };

    int s = 2*n*m, t = 2*n*m + 1;
    Dinic<lli> D(t + 1);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            auto ch = mat[i][j];
            if(ch != '.' && ch != 'B'){
                D.addEdge(mapping(i, j, false), mapping(i, j, true), cost[ ch - 'a' ]);
            }
            else {
                D.addEdge(mapping(i, j, false), mapping(i, j, true), INF_D);
            }
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            auto ch = mat[i][j];

            if(i == 0 || i == n-1 || j == 0 || j == m-1){
                D.addEdge(mapping(i, j, true), t, INF_D);
            }
            
            if(ch == 'B'){
                D.addEdge(s, mapping(i, j, false), INF_D);
            }

            for(auto [dx, dy]: dir){
                if(is_inside(i + dx, j + dy)) {
                    D.addEdge(mapping(i, j, true), mapping(i+dx, j+dy, false), INF_D);
                }
            }
        }
    }

    auto ans = D.StartDinic(s, t);
    // cout << ans << endl;
    cout << (ans < INF_D ? ans : -1) << endl;








	return 0;
}

