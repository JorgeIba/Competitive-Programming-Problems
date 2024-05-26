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


#define point pair<int,int>


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
    T limit = 1;
    T maxFlow = 0;
    const bool scaling = false;


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
        while(!q.empty())
        {
            lli u = q.front(); q.pop();
            for(auto E: adjList[u])
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
    
    T StartDinic(int s, int t){
        maxFlow = 0;
        for(limit = (scaling?1<<30:1); limit>0; limit>>=1){ 
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


template<typename T = int>
struct LowerBoundDinic: Dinic<T>{
    vector< T > dem;
    int n;
    int s_prime = n, t_prime = n+1;

    LowerBoundDinic(int n): Dinic<T>(n+2), dem(n), n(n), s_prime(n), t_prime(n+1) {}

    void addEdge(int u, int v, T l, T r) {
        dem[u] += l;
        dem[v] -= l;
        Dinic<T>::addEdge(u, v, r - l);
    }

    bool has_circulation() {
        T total_dem = 0;
        for(int i = 0; i < n; i++){
            if(dem[i] < 0) {
                total_dem += -dem[i];
                addEdge(s_prime, i, 0, -dem[i]);
            } else if(dem[i] > 0){
                addEdge(i, t_prime, 0, dem[i]);
            }
        }

        return Dinic<T>::StartDinic(s_prime, t_prime) == total_dem;
    }

    T maxFlow(int s, int t) {
        addEdge(t, s, 0, INF);
        if(!has_circulation()) return -1;

        Dinic<T>::maxFlow = 0;
        return Dinic<T>::StartDinic(s, t);
    }
};




int main () {
	fastIO();
    int n, m; cin>>n>>m;
    lli r, b; cin>>r>>b;


    vector< lli > xs, ys;
    vector< point > points(n);
    for(auto &p: points) cin>>p.first>>p.second;

    for(auto p: points) xs.push_back(p.first), ys.push_back(p.second);

    sort(all(xs));
    sort(all(ys));

    xs.erase(unique(all(xs)), xs.end());
    ys.erase(unique(all(ys)), ys.end());

    unordered_map<int, int> map_x, map_y;

    auto mapping_xs = [&](lli x) {
        if(!map_x.count(x))
            map_x[x] = SZ(map_x);
        return map_x[x];
    };

    auto mapping_ys = [&](lli y) {
        if(!map_y.count(y))
            map_y[y] = SZ(map_y);

        return map_y[y];
    };

    for(auto x: xs) mapping_xs(x);
    for(auto y: ys) mapping_ys(y);

    
    vector< int > min_dx( SZ(xs), 1e9 ), min_dy( SZ(ys), 1e9 );

    for(int i = 0; i < m; i++){
        int t, l, d; cin>>t>>l>>d;
        if(t == 1) {
            if(!map_x.count(l)) continue;

            int &mini = min_dx[  mapping_xs(l) ];
            mini = min(mini, d);
        } else {
            if(!map_y.count(l)) continue;

            int &mini = min_dy[  mapping_ys(l) ];
            mini = min(mini, d);
        }
    }


    vector<int> total_x(  SZ(xs)  ), total_y(  SZ(ys)  );
    for(auto p: points){
        total_x[  mapping_xs(p.first)   ]++;
        total_y[  mapping_ys(p.second)  ]++;
    }


    int left = SZ(xs), middle = SZ(points), right = SZ(ys);
    int s = left + middle + right, t = s+1;

    int N = left+middle+right+2;

    LowerBoundDinic<lli> *LBD = new LowerBoundDinic<lli>(N);

    bool impossible = false;
    for(int i = 0; i < SZ(xs); i++){
        int total = total_x[i], min_d = min_dx[i];
        int lower = (total-min_d) / 2 + ((total-min_d) % 2);
        int upper = (total+min_d) / 2;

        if(lower > upper) impossible = true;

        lower = max(0, lower);
        upper = min(upper, total);

        LBD->addEdge(s, i, lower, upper);
    }

    for(int i = 0; i < SZ(points); i++){
        auto [x, y] = points[i];
        LBD->addEdge(mapping_xs(x), left + i, 0, 1);
        LBD->addEdge(left + i, left + middle + mapping_ys(y), 0, 1);
    }

    for(int i = 0; i < SZ(ys); i++){
        int total = total_y[i], min_d = min_dy[i];
        int lower = (total-min_d) / 2 + ((total-min_d) % 2);
        int upper = (total+min_d) / 2;

        if(lower > upper) impossible = true;

        lower = max(0, lower);
        upper = min(upper, total);
        LBD->addEdge(left + middle + i, t, lower, upper);
    }

    if(impossible) {
        cout << -1 << endl;
        return 0;
    }

    auto n_ans = LBD->maxFlow(s, t);

    if(n_ans == -1) {
        cout << n_ans << endl;
        return 0;
    }


    pair<int, char> red = {r, 'r'}, blue = {b, 'b'};
    auto best = min(red, blue);
    auto worst = max(red, blue);


    vector<int> idx_ans;
    for(int i = 0; i < SZ(points); i++){
        for(auto v: LBD->adjList[left + i]){
            if(v->rev) continue;
            if(v->flow) {
                idx_ans.push_back(i);
            }
        }
    }

    string s_ans(n, worst.second);
    for(auto x: idx_ans)
        s_ans[x] = best.second;


    cout << 1LL*n_ans * best.first + 1LL*(n - n_ans) * worst.first << endl;
    cout << s_ans << endl;
        


    




	return 0;
}

