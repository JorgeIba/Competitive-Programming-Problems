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

template <typename T = int> struct Edge {
    int to;
    T flow, capacity;
    bool rev;
    Edge *res;
    Edge(int to, T capacity, bool rev = false)
        : to(to), flow(0), capacity(capacity), rev(rev) {}
    void addFlow(T flow) {
        this->flow += flow;
        this->res->flow -= flow;
    }
};

const int INF = 1e9;

template <typename T = int> struct Dinic {
    vector<vector<Edge<T> *>> adjList;
    vector<int> pos, dist;
    int N;
    T maxFlow = 0;

    Dinic(int N) : N(N) {
        adjList.resize(N);
        pos.resize(N);
        dist.resize(N);
    }

    void addEdge(int u, int v, T capacity, bool directed = true) {
        Edge<T> *uv = new Edge<T>(v, capacity, false);
        Edge<T> *vu = new Edge<T>(u, directed ? 0 : capacity, true);
        uv->res = vu;
        vu->res = uv;
        adjList[u].push_back(uv);
        adjList[v].push_back(vu);
    }

    T BlockingFlow(int u, int t, T flow) {
        if (u == t)
            return flow;
        for (int &i = pos[u]; i < (int)adjList[u].size(); i++) {
            Edge<T> *E = adjList[u][i];
            if (E->capacity > E->flow && dist[E->to] == dist[u] + 1) {
                lli f =
                    BlockingFlow(E->to, t, min(flow, E->capacity - E->flow));
                if (f > 0) {
                    E->addFlow(f);
                    return f;
                }
            }
        }
        return 0;
    }
    bool bfs(int s, int t) {
        fill(all(dist), -1);
        queue<int> q;
        q.push(s);
        dist[s] = 0;
        while (!q.empty()) {
            lli u = q.front();
            q.pop();
            for (auto E : adjList[u]) {
                if (dist[E->to] == -1 && E->capacity > E->flow){
                    dist[E->to] = dist[u] + 1;
                    q.push(E->to);
                }
            }
        }
        return dist[t] != -1;
    }

    T StartDinic(int s, int t) {
        while (bfs(s, t)) {
            lli f = 0;
            fill(all(pos), 0);
            while ((f = BlockingFlow(s, t, INF))) {
                maxFlow += f;
            }
        }
        return maxFlow;
    }

    bool FindCycle(int start, int n, int m, int s, int t) {
        vector<int> visited(N);

        auto dfs = [&](const auto &dfs, int u, int start) {
            if(u == start) {
                return true;
            }

            for(auto E: adjList[u]) {
                if(visited[E->to]) continue;
                if(E->capacity - E->flow > 0) {
                    visited[E->to] = true;
                    if(dfs(dfs, E->to, start)) {
                        return true;
                    }
                }
            }
            return false;
        };

        for(auto E: adjList[start]) {
            if(visited[E->to]) continue;

            if((E->res->flow == 1 && E->to == s)) {
                visited[E->to] = true;
                if(dfs(dfs, E->to, start)) {
                    return true;
                }
            } else if(E->flow == 1 && E->to == t) {
                visited[start] = true;
                if(dfs(dfs, start, t)) {
                    return true;
                }
            }
        }

        return false;
    }

    bool InMatching(int curr) {
        for(auto E: adjList[curr]) {
            if(E->flow == 1) {
                return true;
            }
        }
        return false;
    }
};


vector< pair<int,int> > deltas = {
    {-1, 0},
    {0, -1}, {0, 1},
    {1, 0}
};

int main () {
	// fastIO();

    int n, m; cin>>n>>m;

    vector<string> mat(n);
    for(auto &s: mat) cin>>s;

    auto get_index = [&](int x, int y) {
        return x * m + y;
    };  

    auto is_inside = [&](int x, int y) {
        return (0 <= x && x < n && 0 <= y && y < m);
    };


    int s = n*m, t = s+1;
    Dinic<int> D(t+1);
    
    forn(i, n) {
        forn(j, m) {
            if((i+j) % 2 == 0) {
                D.addEdge(s, get_index(i, j), 1);
            } else {
                D.addEdge(get_index(i, j), t, 1);
                continue;
            }

            if(mat[i][j] != '.') continue;

            for(auto [dx, dy]: deltas) {
                if(!is_inside(i+dx, j+dy) || mat[i+dx][j+dy] != '.') continue;
                D.addEdge(get_index(i, j), get_index(i+dx, j+dy), 1);
            }
        }
    }

    D.StartDinic(s, t);

    int ans = 0;
    
    forn(i, n) {
        forn(j, m) {
            if(mat[i][j] != '.') continue;

            if(!D.InMatching(get_index(i, j))){
                ans++;
            } else {
                auto poss_remove = D.FindCycle(get_index(i, j), n, m, s, t);
                ans += (poss_remove);
            }            
        }
    }

    cout << ans << endl;


	return 0;
}

