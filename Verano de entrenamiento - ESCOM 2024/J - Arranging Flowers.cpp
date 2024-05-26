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

// MUCHO OJO CON ESTO
const int INF = 1e9;

const int MAXN = 220 + 5;

int mat[MAXN][MAXN];
bool possible[MAXN][MAXN];
bool visited[2*MAXN];

template <typename T = int> struct Dinic {
    int N;
    vector<vector<Edge<T> *>> adjList;
    vector<int> pos, dist;
    T maxFlow = 0;

    Dinic(int N) : N(N), adjList(N), pos(N), dist(N) {}

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
                if (dist[E->to] == -1 && E->capacity > E->flow) {
                    dist[E->to] = dist[u] + 1;
                    q.push(E->to);
                }
            }
        }
        return dist[t] != -1;
    }

    T StartDinic(int s, int t) {
        maxFlow = 0;

        while (bfs(s, t)) {
            lli f = 0;
            fill(all(pos), 0);
            while ((f = BlockingFlow(s, t, INF))) {
                maxFlow += f;
            }
        }
        return maxFlow;
    }


    bool TryCycle(int curr, const int start, vector<Edge<T>*> &cycle) {
        if(curr == start) {
            return true;
        }
        if(visited[curr]) return false;

        visited[curr] = true;
        for(Edge<T> *E: adjList[curr]) {
            if(E->capacity - E->flow == 0) continue;
            if(E->to < start) continue; // do not modify any position lower than start

            if(TryCycle(E->to, start, cycle)){
                cycle.push_back(E);
                return true;
            }
        }
        // visited[curr] = false;

        return false;
    }
    

    void LexSmallest(int n) {
        // Assume edges are already ordered
        vector<bool> already(n);
        forn(i, n) {
            if(already[i]) continue; // Already found it in previous cycle

            // Try with smallest at i-th position            
            for(Edge<T> *E: adjList[i]) {
                if(E->flow == 1) break;
                if(E->capacity - E->flow == 0) continue;

                vector<Edge<T>*> cycle;
                fill(visited, visited+2*n, false);
                if(TryCycle(E->to, i, cycle)){
                    cycle.push_back(E);
                    for(auto E: cycle) {
                        if(E->to < n) already[E->to] = true; // Other position moved

                        assert(E->capacity - E->flow > 0);
                        E->addFlow(1);
                    }
                    break;
                }
            }
        }
    }
};

int ans[MAXN][MAXN];

void solve() {
    int n, m; cin>>n>>m;

    forn(i, n)
        forn(j, n)
            possible[i][j] = true;

    forn(i, m){
        forn(j, n) {
            cin>>mat[i][j];
            mat[i][j]--;
            possible[j][mat[i][j]] = false;
        }
    }


    int s = 2*n, t = s+1;
    Dinic<int> D(t+1);

    for(int i = 0; i < n; i++) {
        forn(j, n) {
            if(possible[i][j]) {
                D.addEdge(i, n + j, 1);
            }
        }

        D.addEdge(s, i, 1);
        D.addEdge(n+i, t, 1);
    }

 
    forn(row, n-m) {
        auto ansFlow = D.StartDinic(s, t);
        assert(ansFlow == n);
        D.LexSmallest(n); // Improve match (lexicographically)

        forn(i, n){
            for(auto E: D.adjList[i]) {
                if(E->to == s) continue;
                if(E->flow == 1) {
                    // Disable this edge for future
                    ans[row][i] = E->to - n;

                    E->flow = 0;
                    E->capacity = 0;
                    E->res->flow = 0;
                    E->res->capacity = 0;
                }
            }
        }

        // Reset to other run
        for(auto E: D.adjList[s]) {
            E->flow = 0;
            E->res->flow = 0;
        }
        for(auto E: D.adjList[t]) {
            E->flow = 0;
            E->res->flow = 0;
        }
    }

    // Print Answer
    cout << n-m << endl;   
    forn(i, n-m){
        forn(j, n) {
            cout << ans[i][j]+1;
            if(j != n-1) cout << " ";
        }
        cout << endl;
    }

}

int main () {
	fastIO();

    int t; cin>>t;

    while(t--) {
        solve();
        cout << endl;
    }

	return 0;
}
